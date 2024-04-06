#include "../Include/sema.h"
#include <gtest/gtest.h>

TEST(UnaryExpressionsRvalue, UnaryExpressionsCheck) {
  std::string a = R"(
        a:int = -5;
    )";

  DonsusParser::end_result result = Du_Parse(a);

  donsus_ast::donsus_node_type::underlying type =
      result->get_nodes()[0]->children[0]->type.type;

  EXPECT_EQ(donsus_ast::donsus_node_type::DONSUS_UNARY_EXPRESSION, type);
}
