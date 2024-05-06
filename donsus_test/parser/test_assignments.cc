#include "parser.h"
#include <gtest/gtest.h>

#include <iostream>

/** \brief Check for assignment's name
 * */
TEST(AssignmentName, AssignmentName) {
  std::string a = R"(
    a:int = 12;
    a = 11;
)";
  DonsusParser::end_result result = Du_Parse(a);
  // get the lvalue node of the assignment
  utility::handle<donsus_ast::node> lvalue =
      result->get_nodes()[1]->get<donsus_ast::assignment>().lvalue;
  // get the name of the rvalue node
  utility::handle<donsus_ast::node> rvalue =
      result->get_nodes()[1]->get<donsus_ast::assignment>().rvalue;
  EXPECT_EQ(donsus_ast::donsus_node_type::DONSUS_IDENTIFIER, lvalue->type.type);
  EXPECT_EQ(donsus_ast::donsus_node_type::DONSUS_NUMBER_EXPRESSION,
            rvalue->type.type);
  EXPECT_EQ(donsus_token_kind::DONSUS_EQUAL,
            result->get_nodes()[1]->get<donsus_ast::assignment>().op.kind);
}

TEST(AssignmentArrayAccess, AssignmentTest) {
  std::string a = R"(
    a:int[] = [12, 11];
    a[0] = 10;  
)";

  DonsusParser::end_result result = Du_Parse(a);
  // get the lvalue node of the assignment
  utility::handle<donsus_ast::node> lvalue =
      result->get_nodes()[1]->get<donsus_ast::assignment>().lvalue;
  // get the name of the rvalue node
  utility::handle<donsus_ast::node> rvalue =
      result->get_nodes()[1]->get<donsus_ast::assignment>().rvalue;
  EXPECT_EQ(donsus_ast::donsus_node_type::DONSUS_ARRAY_ACCESS,
            lvalue->type.type);
  EXPECT_EQ("a", lvalue->get<donsus_ast::array_access>().identifier_name);
  EXPECT_EQ(donsus_ast::donsus_node_type::DONSUS_NUMBER_EXPRESSION,
            lvalue->get<donsus_ast::array_access>().index->type.type);
  EXPECT_EQ(donsus_ast::donsus_node_type::DONSUS_NUMBER_EXPRESSION,
            rvalue->type.type);
}