//===----------------------------------------------------------------------===//
//
//                        JFS - The JIT Fuzzing Solver
//
// Copyright 2017 Daniel Liew
//
// This file is distributed under the MIT license.
// See LICENSE.txt for details.
//
//===----------------------------------------------------------------------===//
#include "jfs/Core/SMTLIB2Parser.h"
#include "jfs/Core/ScopedJFSContextErrorHandler.h"
#include "jfs/Core/Z3Node.h"
#include "z3.h"

namespace jfs {
namespace core {
SMTLIB2Parser::SMTLIB2Parser(JFSContext &ctx) : ctx(ctx), errorCount(0) {}
SMTLIB2Parser::~SMTLIB2Parser() {}

std::shared_ptr<Query> SMTLIB2Parser::parseFile(llvm::StringRef fileName) {
  Z3ASTHandle constraint;
  ScopedJFSContextErrorHandler errorHandler(ctx, this);
  constraint =
      Z3ASTHandle(Z3_parse_smtlib2_file(ctx.z3Ctx, fileName.str().c_str(),
                                        /*num_sorts=*/0,
                                        /*sort_names=*/0,
                                        /*sorts=*/0,
                                        /*num_decls=*/0,
                                        /*decl_names=*/0,
                                        /*decls=*/0),
                  ctx.z3Ctx);
  if (errorCount > 0) {
    return nullptr;
  }
  // TODO: Make the query object
  return nullptr;
}

JFSContextErrorHandler::ErrorAction
SMTLIB2Parser::handleZ3error(JFSContext &ctx, Z3_error_code ec) {
  ++errorCount;
  return JFSContextErrorHandler::CONTINUE;
}
}
}
