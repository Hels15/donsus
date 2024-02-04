// AST TREE API FOR PARSER.CC
#include "../Include/parser.h"
#include <memory>

std::unique_ptr<donsus_ast> make_ast_node(donsus_token& value, std::unique_ptr<donsus_ast> left, std::unique_ptr<donsus_ast> right) {
    std::unique_ptr<donsus_ast> n = std::make_unique<donsus_ast>();

    n->value = value;
    n->left = std::move(left);
    n->right = std::move(right);

    return n;
}

std::unique_ptr<donsus_ast> donsus_make_ast_leaf(donsus_token &value) {
    return make_ast_node(value, nullptr, nullptr);
}

std::unique_ptr<donsus_ast> donsus_make_ast_unary(donsus_token& value, std::unique_ptr<donsus_ast> left) {
    return make_ast_node(value, std::move(left), nullptr);
}