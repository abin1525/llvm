//==-- WebAssemblyTargetStreamer.h - WebAssembly Target Streamer -*- C++ -*-==//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file declares WebAssembly-specific target streamer classes.
/// These are for implementing support for target-specific assembly directives.
///
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_WEBASSEMBLY_MCTARGETDESC_WEBASSEMBLYTARGETSTREAMER_H
#define LLVM_LIB_TARGET_WEBASSEMBLY_MCTARGETDESC_WEBASSEMBLYTARGETSTREAMER_H

#include "llvm/BinaryFormat/Wasm.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/Support/MachineValueType.h"

namespace llvm {

class MCWasmStreamer;
class MCSymbolWasm;

/// WebAssembly-specific streamer interface, to implement support
/// WebAssembly-specific assembly directives.
class WebAssemblyTargetStreamer : public MCTargetStreamer {
public:
  explicit WebAssemblyTargetStreamer(MCStreamer &S);

  /// .param
  virtual void emitParam(MCSymbol *Symbol, ArrayRef<MVT> Types) = 0;
  /// .result
  virtual void emitResult(MCSymbol *Symbol, ArrayRef<MVT> Types) = 0;
  /// .local
  virtual void emitLocal(ArrayRef<MVT> Types) = 0;
  /// .endfunc
  virtual void emitEndFunc() = 0;
  /// .functype
  virtual void emitIndirectFunctionType(MCSymbolWasm *Symbol) = 0;
  /// .indidx
  virtual void emitIndIdx(const MCExpr *Value) = 0;
  /// .globaltype
  virtual void emitGlobalType(MCSymbolWasm *Sym) = 0;
  /// .eventtype
  virtual void emitEventType(MCSymbolWasm *Sym) = 0;
  /// .import_module
  virtual void emitImportModule(MCSymbolWasm *Sym, StringRef ModuleName) = 0;

protected:
  void emitValueType(wasm::ValType Type);
};

/// This part is for ascii assembly output
class WebAssemblyTargetAsmStreamer final : public WebAssemblyTargetStreamer {
  formatted_raw_ostream &OS;

public:
  WebAssemblyTargetAsmStreamer(MCStreamer &S, formatted_raw_ostream &OS);

  void emitParam(MCSymbol *Symbol, ArrayRef<MVT> Types) override;
  void emitResult(MCSymbol *Symbol, ArrayRef<MVT> Types) override;
  void emitLocal(ArrayRef<MVT> Types) override;
  void emitEndFunc() override;
  void emitIndirectFunctionType(MCSymbolWasm *Symbol) override;
  void emitIndIdx(const MCExpr *Value) override;
  void emitGlobalType(MCSymbolWasm *Sym) override;
  void emitEventType(MCSymbolWasm *Sym) override;
  void emitImportModule(MCSymbolWasm *Sym, StringRef ModuleName) override;
};

/// This part is for Wasm object output
class WebAssemblyTargetWasmStreamer final : public WebAssemblyTargetStreamer {
public:
  explicit WebAssemblyTargetWasmStreamer(MCStreamer &S);

  void emitParam(MCSymbol *Symbol, ArrayRef<MVT> Types) override;
  void emitResult(MCSymbol *Symbol, ArrayRef<MVT> Types) override;
  void emitLocal(ArrayRef<MVT> Types) override;
  void emitEndFunc() override;
  void emitIndirectFunctionType(MCSymbolWasm *Symbol) override;
  void emitIndIdx(const MCExpr *Value) override;
  void emitGlobalType(MCSymbolWasm *Sym) override;
  void emitEventType(MCSymbolWasm *Sym) override;
  void emitImportModule(MCSymbolWasm *Sym, StringRef ModuleName) override;
};

} // end namespace llvm

#endif
