#include <ctype.h>
#include <iomanip>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "TFile.h"
#include "TH1.h"
#include "TH1F.h"
#include "TH2.h"
#include "TTree.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <TROOT.h>
#include <TString.h>
#include <TStyle.h>
#include <TSystem.h>
#include <TCanvas.h>
#include <TMarker.h>
#include <THStack.h>
#include <TLegend.h>
#include <TLatex.h>
#include <TCut.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TLorentzVector.h>
#include <TMath.h>
#include <TF1.h>


const int njets = 300;

typedef struct {
   Float_t eta[njets];
   Float_t pt[njets];
   Float_t phi[njets];
	Float_t mass[njets];
	Float_t btag[njets];
	Int_t nsoft;
	Float_t soft_pt[njets];
	Float_t soft_eta[njets];
	Float_t soft_mass[njets];
	Float_t qgl[njets];
	Int_t nsoft2;
	Int_t nsoft5;
	Int_t nsoft10;
	Int_t id[njets];
	Float_t HTsoft;			
} Jets;

using namespace std;

void analyzer_data40pb_singleBtag(int files, int files_max){
    
const int nfiles  = 1;

TString file_names[nfiles] = {"tree_BTagCSV.root"};
   
TString type[nfiles] = {"Data40pb_SingleBtag"};

do {
	
	Float_t presel=0;
	Float_t cut1 = 0;
	Float_t cut2 = 0;
	Float_t cut3 = 0;
	Float_t cut4 = 0;
	Float_t cut5 = 0;
	Float_t genweight=1.;
	Int_t global_counter = 0;
	Bool_t HLT_QuadPFJet_SingleBTag_CSV_VBF_Mqq460;
	TFile *file_initial = new TFile(file_names[files]);
   TTree *tree_initial = (TTree*)file_initial->Get("tree");
    Jets Jet;
    Float_t v_type;
    Float_t wrong_type=0.;
    Int_t nJets;
	Int_t JSON = 0;


    tree_initial->SetBranchAddress("offJet_num",&nJets);
    tree_initial->SetBranchAddress("offJet_pt",Jet.pt);
    tree_initial->SetBranchAddress("offJet_eta",Jet.eta);
    tree_initial->SetBranchAddress("offJet_phi",Jet.phi);
	tree_initial->SetBranchAddress("offJet_mass",Jet.mass);
	tree_initial->SetBranchAddress("offJet_csv",Jet.btag);
 	tree_initial->SetBranchAddress("HLT_QuadPFJet_SingleBTagCSV_VBF_Mqq460_v2",&HLT_QuadPFJet_SingleBTag_CSV_VBF_Mqq460);
	tree_initial->SetBranchAddress("JSON",&JSON);
 	
    
    TH1F *hJet1_pt_bin = new TH1F("hJet1_pt_bin", "", 50, 90., 140.);
    hJet1_pt_bin->GetXaxis()->SetTitle("1st Jet p_{T} (GeV)");
    TH1F *hJet2_pt_bin = new TH1F("hJet2_pt_bin", "", 40, 70., 110.);
    hJet2_pt_bin->GetXaxis()->SetTitle("2nd Jet p_{T} (GeV)");
    TH1F *hJet3_pt_bin = new TH1F("hJet3_pt_bin", "", 30, 60., 90.);
    hJet3_pt_bin->GetXaxis()->SetTitle("3rd Jet p_{T} (GeV)");
    TH1F *hJet4_pt_bin = new TH1F("hJet4_pt_bin", "", 40, 30., 70.);
    hJet4_pt_bin->GetXaxis()->SetTitle("4th Jet p_{T} (GeV)");
	TH1F *hMqq_bin = new TH1F("hMqq_bin","",50.,200.,250.);
	hMqq_bin->GetXaxis()->SetTitle("m_{qq} (GeV)");


    TH1F *hJet1_pt = new TH1F("hJet1_pt", "", 30, 0., 600.);
    hJet1_pt->GetXaxis()->SetTitle("1st Jet p_{T} (GeV)");
    TH1F *hJet2_pt = new TH1F("hJet2_pt", "", 30, 0., 600.);
    hJet2_pt->GetXaxis()->SetTitle("2nd Jet p_{T} (GeV)");
    TH1F *hJet3_pt = new TH1F("hJet3_pt", "", 20, 0., 400.);
    hJet3_pt->GetXaxis()->SetTitle("3rd Jet p_{T} (GeV)");
    TH1F *hJet4_pt = new TH1F("hJet4_pt", "", 20, 0., 400.);
    hJet4_pt->GetXaxis()->SetTitle("4th Jet p_{T} (GeV)");
    
    TH1F *hJet5_pt = new TH1F("hJet5_pt", "", 25, 0., 500.);
    hJet5_pt->GetXaxis()->SetTitle("5th Jet p_{T} (GeV)");
    
	TH1F *hJet1_eta = new TH1F("hJet1_eta", "", 20, -5., 5.);
    hJet1_eta->GetXaxis()->SetTitle("1st Jet #eta");
    TH1F *hJet2_eta = new TH1F("hJet2_eta", "", 20, -5., 5.);
    hJet2_eta->GetXaxis()->SetTitle("2nd Jet #eta");
    TH1F *hJet3_eta = new TH1F("hJet3_eta", "", 20, -5., 5.);
    hJet3_eta->GetXaxis()->SetTitle("3rd Jet #eta");
    TH1F *hJet4_eta = new TH1F("hJet4_eta", "", 20, -5., 5.);
    hJet4_eta->GetXaxis()->SetTitle("4th Jet #eta");
    
    TH1F *hJet1_phi = new TH1F("hJet1_phi", "", 32,-3.2,3.2);
    hJet1_phi->GetXaxis()->SetTitle("1st Jet #phi");
    TH1F *hJet2_phi = new TH1F("hJet2_phi", "", 32,-3.2,3.2);
    hJet2_phi->GetXaxis()->SetTitle("2nd Jet #phi");
    TH1F *hJet3_phi = new TH1F("hJet3_phi", "", 32,-3.2,3.2);
    hJet3_phi->GetXaxis()->SetTitle("3rd Jet #phi");
    TH1F *hJet4_phi = new TH1F("hJet4_phi", "", 32,-3.2,3.2);
    hJet4_phi->GetXaxis()->SetTitle("4th Jet #phi");
    TH1F *hVtype = new TH1F("hVtype","", 6,-1.,6.);
    hVtype->GetXaxis()->SetTitle("vtype");

	TH1F *hMqq = new TH1F("hMqq","",100.,0.,3000.);
	hMqq->GetXaxis()->SetTitle("m_{qq} (GeV)");
   
	TH1F *hEtaQQ = new TH1F("hEtaQQ","",80,0.,8.);
	hEtaQQ->GetXaxis()->SetTitle("|#Delta#eta_{qq}|");
    
	TH1F *hPhiBB = new TH1F("hPhiBB","",32,0.,3.2);
	hPhiBB->GetXaxis()->SetTitle("|#Delta#phi_{bb}|");
	
    
	
	TH1F* hMbb = new TH1F("hMbb","",250,0.,250.);
	hMbb->GetXaxis()->SetTitle("m_{bb} (GeV)");

	TH1F *hbtag = new TH1F("hbtag","",110,0.,1.1);
	hbtag->GetXaxis()->SetTitle("CSV 1^{st} b-jet");
 
	TH1F *hbtag2 = new TH1F("hbtag2","",110,0.,1.1);
	hbtag2->GetXaxis()->SetTitle("CSV 2^{nd} b-jet");
	
	
	TH1F *hcosOqqbb = new TH1F("hcosOqqbb","",100,-1.,1.);
	hcosOqqbb->GetXaxis()->SetTitle("cos(#theta_{bb_qq})");
	TH1F *hEtaQB1 = new TH1F("hEtaQB1","",160.,-8.,8.);
	hEtaQB1->GetXaxis()->SetTitle("#Delta#eta_{qb}^{forward}");
	TH1F *hEtaQB2 = new TH1F("hEtaQB2","",160.,-8.,8.);
	hEtaQB2->GetXaxis()->SetTitle("#Delta#eta_{qb}^{backward}");
	TH1F *hPhiQB1 = new TH1F("hPhiQB1","",32,0.,3.2);
	hPhiQB1->GetXaxis()->SetTitle("#Delta#phi_{qb}^{forward}");
	TH1F *hPhiQB2 = new TH1F("hPhiQB2","",32,0.,3.2);
	hPhiQB2->GetXaxis()->SetTitle("#Delta#phi_{qb}^{backward}");
	TH1F *hx1 = new TH1F("hx1","",100.,0.,1.);
	hx1->GetXaxis()->SetTitle("x_{1}");
	TH1F *hx2 = new TH1F("hx2","",100.,0.,1.);
	hx2->GetXaxis()->SetTitle("x_{2}");
	TH1F *hVB1_mass = new TH1F("hVB1_mass","",100,0.,1000.);
	hVB1_mass->GetXaxis()->SetTitle("M_{W'_{1}} (GeV)");
	TH1F *hVB2_mass = new TH1F("hVB2_mass","",100.,0.,1000.);
	hVB2_mass->GetXaxis()->SetTitle("M_{W'_{2}} (GeV)");

	TH1F* hEtot = new TH1F("hEtot","",150.,0.,6000.);
	hEtot->GetXaxis()->SetTitle("E^{tot} (GeV)");
	TH1F* hPxtot= new TH1F("hPxtot","",100,-500.,500.);
	hPxtot->GetXaxis()->SetTitle("P_{x}^{tot} (GeV)");
	TH1F* hPytot= new TH1F("hPytot","",100,-500.,500.);
	hPytot->GetXaxis()->SetTitle("P_{y}^{tot} (GeV)");
	TH1F* hPztot= new TH1F("hPztot","",100,-5000.,5000);
	hPztot->GetXaxis()->SetTitle("P_{z}^{tot} (GeV)");

	
	TH1F *hPtqqbb = new TH1F("hPtqqbb","",50.,0.,500.);
	hPtqqbb->GetXaxis()->SetTitle("p_{T} of qqbb system (GeV)");
	TH1F *hPhiqqbb = new TH1F("hPhiqqbb","",32,-3.2,3.2);
	hPhiqqbb->GetXaxis()->SetTitle("-#phi of qqbb system");
	TH1F *hEtaqqbb = new TH1F("hEtaqqbb","",160,-8,8);
	hEtaqqbb->GetXaxis()->SetTitle("#eta of qqbb system");



   		const int numArray= 40;
   		TH1F* histArray[numArray] = {hJet1_pt,hJet2_pt,hJet3_pt,hJet4_pt,  hJet1_eta,hJet2_eta,hJet3_eta,hJet4_eta,  hJet1_phi,hJet2_phi,hJet3_phi,hJet4_phi, hMqq, hEtaQQ, hPhiBB,hMbb,hbtag,hbtag2,hcosOqqbb,hEtaQB1, hEtaQB2, hPhiQB1, hPhiQB2,hx1,hx2,hVB1_mass, hVB2_mass, hEtot, hPxtot, hPytot, hPztot, hJet5_pt,hPtqqbb, hPhiqqbb, hEtaqqbb, hJet1_pt_bin,hJet2_pt_bin,hJet3_pt_bin,hJet4_pt_bin, hMqq_bin };

			for (int i=0;i<numArray;i++){
				histArray[i]->Sumw2();
			}

	int nentries = tree_initial->GetEntries() ;
    for (int entry=0; entry<nentries;++entry){
        tree_initial->GetEntry(entry);


		if (JSON!=1) {
			continue;
		}
		
		if (!((Jet.pt[0]>92.)&&(Jet.pt[1]>76.)&&(Jet.pt[2]>64.)&&(Jet.pt[3]>30.))) continue;
		cut1++;

		int loopJet_min = 4;
		if (nJets<4) loopJet_min=nJets;


		Double_t btag_max = 0.7;
		int btag_max1_number = -1;
		int btag_max2_number = -1;
		for (int i=0;i<loopJet_min;i++){
			if ((Jet.btag[i]>btag_max)){
				btag_max=Jet.btag[i];
				btag_max1_number=i;
			}
		}
		if (!((btag_max1_number>=0))) continue;
		TLorentzVector Bjet1;
		Bjet1.SetPtEtaPhiM(Jet.pt[btag_max1_number],Jet.eta[btag_max1_number],Jet.phi[btag_max1_number],Jet.mass[btag_max1_number]);


		int pt_max1_number = -1;
		int pt_max2_number = -1;

		TLorentzVector js[3];
		int jcount = 0;
		int j_num[3] = {};
		for (int i=0;i<4;i++){
			if ((i!=btag_max1_number)) {
				js[jcount].SetPtEtaPhiM(Jet.pt[i], Jet.eta[i], Jet.phi[i], Jet.mass[i]);
				j_num[jcount] = i;
				jcount++;
			}
		}	
		if (!(jcount==3)) continue;
	
		Float_t deltaEtaJets[3] = {TMath::Abs(js[0].Eta()-js[1].Eta()),TMath::Abs(js[1].Eta()-js[2].Eta()), TMath::Abs(js[0].Eta()-js[2].Eta())};
		int eta_num[3][2] = {{0,1}, {1,2} ,{0,2}};
		Float_t max_deltaEta = 0.;
		int max_deltaEta_num = -1;
		for (int i=0;i<3;i++){
			if (deltaEtaJets[i]>max_deltaEta) {
				max_deltaEta = deltaEtaJets[i];
				max_deltaEta_num = i;
			}
		}
		
		pt_max1_number = j_num[ eta_num[max_deltaEta_num][0]];
		pt_max2_number = j_num[ eta_num[max_deltaEta_num][1]];

		if (!((pt_max1_number>=0)&&(pt_max2_number>=0))) continue;
	
		TLorentzVector Qjet1;
		Qjet1.SetPtEtaPhiM(Jet.pt[pt_max1_number] ,Jet.eta[pt_max1_number],Jet.phi[pt_max1_number],Jet.mass[pt_max1_number]);
	
		TLorentzVector Qjet2;
		Qjet2.SetPtEtaPhiM(Jet.pt[pt_max2_number],Jet.eta[pt_max2_number],Jet.phi[pt_max2_number],Jet.mass[pt_max2_number]);

		for (int i=0;i<4;i++){
			if ( (i!=btag_max1_number)&&(i!=pt_max1_number)&&(i!=pt_max2_number)) btag_max2_number=i;
		}

		if (!((btag_max2_number>=0))) continue;
		TLorentzVector Bjet2;
		Bjet2.SetPtEtaPhiM(Jet.pt[btag_max2_number],Jet.eta[btag_max2_number],Jet.phi[btag_max2_number],Jet.mass[btag_max2_number]);

		TLorentzVector qq;
		qq = Qjet1+Qjet2;
		Double_t Mqq = qq.M();
		Double_t bbDeltaPhi = TMath::Abs(Bjet1.DeltaPhi(Bjet2));
		Double_t qqDeltaEta = TMath::Abs(Qjet1.Eta()-Qjet2.Eta());
		if (!((Mqq>460)&&(qqDeltaEta>4.1)&&(bbDeltaPhi<1.6))) continue;
		cut2++;

		if (HLT_QuadPFJet_SingleBTag_CSV_VBF_Mqq460!=1) continue;
		cut3++;

		presel++;

		TLorentzVector bb;
		bb = Bjet1+Bjet2;
		Float_t Mbb = bb.M();

		TLorentzVector bbqq;
		bbqq = Bjet1 + Bjet2 + Qjet1 + Qjet2;

		Float_t cosObbqq =TMath::Cos( ( ( Bjet1.Vect() ).Cross(Bjet2.Vect()) ).Angle( ( Qjet1.Vect() ).Cross(Qjet2.Vect()) ) );	

		Float_t EtaBQ1;
	 	Float_t EtaBQ2;
		Float_t PhiBQ1; 	
		Float_t PhiBQ2;
		 if (Qjet1.Eta() >= Qjet2.Eta()) {
			if (Bjet1.Eta() >= Bjet2.Eta())  {
				EtaBQ1 = Qjet1.Eta()-Bjet1.Eta();
				PhiBQ1 = TMath::Abs(Bjet1.DeltaPhi(Qjet1));		
			}
			else {
				EtaBQ1 = Qjet1.Eta()-Bjet2.Eta();
				PhiBQ1 = TMath::Abs(Bjet2.DeltaPhi(Qjet1));	
			}	
		} else if (Bjet1.Eta() >= Bjet2.Eta()) {
				EtaBQ1 = Qjet2.Eta()-Bjet1.Eta();
				PhiBQ1 = TMath::Abs(Bjet1.DeltaPhi(Qjet2));	
				
				}
			else {
				EtaBQ1 = Qjet2.Eta()-Bjet2.Eta();
				PhiBQ1 = TMath::Abs(Bjet2.DeltaPhi(Qjet2));	
			}


		 if (Qjet1.Eta() <= Qjet2.Eta()) {
			if (Bjet1.Eta() <= Bjet2.Eta())  {
				EtaBQ2 = Qjet1.Eta()-Bjet1.Eta();
				PhiBQ2 = TMath::Abs(Bjet1.DeltaPhi(Qjet1));		
			}
			else {
				EtaBQ2 = Qjet1.Eta()-Bjet2.Eta();
				PhiBQ2 = TMath::Abs(Bjet2.DeltaPhi(Qjet1));	
			}	
		} else if (Bjet1.Eta() <= Bjet2.Eta()) {
				EtaBQ2 = Qjet2.Eta()-Bjet1.Eta();
				PhiBQ2 = TMath::Abs(Bjet1.DeltaPhi(Qjet2));	
				
				}
			else {
				EtaBQ2 = Qjet2.Eta()-Bjet2.Eta();
				PhiBQ2 = TMath::Abs(Bjet2.DeltaPhi(Qjet2));	
			}
		


		Float_t Etot = Bjet1.E()+Bjet2.E()+Qjet1.E()+Qjet2.E();
		Float_t PzTot = Bjet1.Pz()+Bjet2.Pz()+Qjet1.Pz()+Qjet2.Pz();
		Float_t PxTot = Bjet1.Px()+Bjet2.Px()+Qjet1.Px()+Qjet2.Px();
		Float_t PyTot = Bjet1.Py()+Bjet2.Py()+Qjet1.Py()+Qjet2.Py();
	
		Float_t x1 = 0.;
		Float_t x2 = 0.;
		x1 = (Etot + PzTot)/2./13000.;
		x2 = (Etot - PzTot)/2./13000.;

		TLorentzVector q1,q2,q1_after,q2_after, VB1, VB2;
		q1.SetPxPyPzE(0.,0.,13000./2.*x1,13000./2.*x1);
		q2.SetPxPyPzE(0.,0.,-13000./2.*x2,13000./2.*x2);
		q1_after.SetPxPyPzE(Qjet1.Px()/Qjet1.Beta(),Qjet1.Py()/Qjet1.Beta(),Qjet1.Pz()/Qjet1.Beta(),Qjet1.E());
		q2_after.SetPxPyPzE(Qjet2.Px()/Qjet2.Beta(),Qjet2.Py()/Qjet2.Beta(),Qjet2.Pz()/Qjet2.Beta(),Qjet2.E());
		if (q1_after.Eta()>=0.) {
			VB1 = -q1_after+q1;
			VB2 = -q2_after+q2;
		} else {
			VB1 = -q2_after+q1;
			VB2 = -q1_after+q2;
		} 
		Float_t VB1_mass, VB2_mass;
		VB1_mass = TMath::Abs(VB1.M());
		VB2_mass = TMath::Abs(VB2.M());


            hJet1_pt->Fill(Jet.pt[0],genweight);
            hJet1_eta->Fill(Jet.eta[0],genweight);
            hJet1_phi->Fill(Jet.phi[0],genweight);
            hJet2_pt->Fill(Jet.pt[1],genweight);
            hJet2_eta->Fill(Jet.eta[1],genweight);
            hJet2_phi->Fill(Jet.phi[1],genweight);
            hJet3_pt->Fill(Jet.pt[2],genweight);
            hJet3_eta->Fill(Jet.eta[2],genweight);
            hJet3_phi->Fill(Jet.phi[2],genweight);
            hJet4_pt->Fill(Jet.pt[3],genweight);
            hJet4_eta->Fill(Jet.eta[3],genweight);
            hJet4_phi->Fill(Jet.phi[3],genweight);
            hJet5_pt->Fill(Jet.pt[4],genweight);
            hVtype->Fill(v_type,genweight);
			hMqq->Fill(Mqq,genweight);
			hEtaQQ->Fill(qqDeltaEta,genweight);
			hPhiBB->Fill(bbDeltaPhi,genweight);
			hMbb->Fill(Mbb,genweight);
			hbtag->Fill(Jet.btag[btag_max1_number],genweight);
			hbtag2->Fill(Jet.btag[btag_max2_number],genweight);
			hcosOqqbb->Fill(cosObbqq,genweight);
			hEtaQB1->Fill(EtaBQ1,genweight);
			hEtaQB2->Fill(EtaBQ2,genweight);
			hPhiQB1->Fill(PhiBQ1,genweight);
			hPhiQB2->Fill(PhiBQ2,genweight);
			hx1->Fill(x1,genweight);
			hx2->Fill(x2,genweight);
			hVB1_mass->Fill(VB1_mass,genweight);
			hVB2_mass->Fill(VB2_mass,genweight);
			hEtot->Fill(Etot,genweight);
			hPxtot->Fill(PxTot,genweight);
			hPytot->Fill(PyTot,genweight);
			hPztot->Fill(PzTot,genweight);
			hPtqqbb->Fill(bbqq.Pt(),genweight);
			hPhiqqbb->Fill((-1)*bbqq.Phi(),genweight);
			hEtaqqbb->Fill(bbqq.Eta(), genweight);
            hJet1_pt_bin->Fill(Jet.pt[0],genweight);
            hJet2_pt_bin->Fill(Jet.pt[1],genweight);
            hJet3_pt_bin->Fill(Jet.pt[2],genweight);
            hJet4_pt_bin->Fill(Jet.pt[3],genweight);
				hMqq_bin->Fill(Mqq,genweight);
			
        }
		TFile file("tree"+type[files]+".root","recreate");
    
		for (int i=0;i<numArray;++i){
    	    	histArray[i]->SetLineWidth(2);
    	   	histArray[i]->GetYaxis()->SetTitle("N_{events}");
       		histArray[i]->GetYaxis()->SetTitleFont(42);
       		histArray[i]->GetYaxis()->SetTitleSize(0.060);
        		histArray[i]->GetYaxis()->SetTitleOffset(0.8);
        		histArray[i]->SetLineColor(kBlue);
        		histArray[i]->Draw();
        		histArray[i]->Write();
   		} 
    		file.Write();
    		file.Close();
	ofstream out("data_"+type[files]+".txt");
	out<< "preselection only = "<< presel<<" , all evetns in the begining = "<<nentries<<", % = "<< (float)presel/nentries<<endl;
	out<<" after cut 1 events left  = "<< cut1<<endl;
	out<<" after cut 2 events left  = "<< cut2<<endl;
	out<<" after cut 3 events left  = "<< cut3<<endl;
	out.close();
	files++;
} while (files<files_max); 

    
}
