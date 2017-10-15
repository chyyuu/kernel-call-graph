#include <set>
#include <vector>
#include <llvm/Pass.h>
#include <llvm/Analysis/InstructionSimplify.h>
#include <llvm/Analysis/ValueTracking.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Operator.h>
#include <llvm/Target/TargetLowering.h>
#include <llvm/Support/CommandLine.h>
#include <llvm/Support/raw_ostream.h>

using std::string;
using std::vector;

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
		int found=0;
 		vector<string> str;
//		errs() << "* " << F.getName() << "\n";
		errs() << F.getName() << " ";
		str.push_back(F.getName());

		for_each_inst(F, I) {
			if (auto CI = dyn_cast<CallInst>(&I)) {
				Function *called = CI->getCalledFunction();
				if (called){
					 found=0;
					 for(vector<string>::iterator i=str.begin();i!=str.end();++i) {
						 if (strcmp((*i).c_str(),called->getName().str().c_str())==0){
							 found =1;
							 break;
						 } 
					 }
				         if(found==0){	
					 	errs() << called->getName() << " ";
						str.push_back(called->getName());
					 }
				}
			}
		}
		errs() << "\n";
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
