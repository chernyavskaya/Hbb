#include "TFile.h"
#include "TString.h"
#include "TSystem.h"
#include "TTree.h"
#include "make_hist.C"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include "TMVA/Factory.h"
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TROOT.h"
#include "TSystem.h"
#include "TApplication.h"

using namespace std;

int main(int argc, char* argv[]){
			  char cmd[50];
	sprintf(cmd,".x make_hist.C(\"%s\",\"%s\",\"%s\")",argv[1],argv[2]); 
	gROOT->ProcessLine(cmd);
	return 0;
}
