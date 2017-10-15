#include <set>

#include <llvm/Pass.h>
#include <llvm/Analysis/InstructionSimplify.h>
#include <llvm/Analysis/ValueTracking.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Operator.h>
#include <llvm/Target/TargetLowering.h>
#include <llvm/Support/CommandLine.h>
#include <llvm/Support/raw_ostream.h>

using namespace llvm;

#define for_each_inst(F, I)						\
	for (auto &_BB : (F).getBasicBlockList())	\
		for (auto &I : _BB.getInstList())

class Play : public FunctionPass {
public:
	static char ID;
	Play() : FunctionPass(ID) {}

	virtual bool doInitialization(Module &M) {
	}

	virtual bool runOnFunction(Function &F) {
		errs() << "* " << F.getName() << "\n";

		for_each_inst(F, I) {
			if (auto CI = dyn_cast<CallInst>(&I)) {
				Function *called = CI->getCalledFunction();
				if (called)
					errs() << "---> " << called->getName() << "\n";
			}
		}
		return true;
	}
};

char Play::ID = 0;

static RegisterPass<Play> X(
	"play", "Random playing w/ bitcode",
	false /* Only looks at CFG */,
	false /* Analysis Pass */);

/**
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 */
