// Running each step in the compiler
#include "../Include/codegen/codegen.h"
#include "../Include/file.h"
#include "../Include/sema.h"
#include <iostream>

int Du_Main(int argc, char **argv) {

  std::string result = handle_file(argv);
  std::string path = argv[1]; // Obtain path
  std::string base_filename =
      path.substr(path.find_last_of("/\\") + 1); // Obtain file name from path

  std::string::size_type p(base_filename.find_last_of('.'));

  std::string file_without_extension =
      base_filename.substr(0, p); // Obtain file without the extension(.du)

  utility::handle<DonsusSymTable> sym_global = new DonsusSymTable();

  // Lexer
  donsus_lexer lexer(result); // initialise lexer
  DonsusParser parser(lexer);

  // Parser
  DonsusParser::end_result parser_result = parser.donsus_parse();

  // build symbol table
  // sema and typecheck
  // see sema.cc for further information
  parser_result->traverse(donsus_sym, sym_global);

#ifdef DEBUG
  std::cout << "\n";
  std::cout << "SYMBOL TABLE:" << std::endl;
  std::cout << "GLOBAL: " << std::endl;
  std::cout << sym_global << std::endl;
#endif
  // sema

  // codegen

  DonsusCodegenEvaluator codegen;
  codegen.compile(parser_result);
  /*  delete sym_global.get();*/
  return 0;
}
