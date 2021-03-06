int preselection_double(Int_t nJets, Float_t Jet_pt[300], Float_t Jet_eta[300], Float_t Jet_phi[300], Float_t Jet_mass[300], Float_t Jet_btagCSV[300], Int_t Jet_id[300], Int_t& btag_max1_number, Int_t& btag_max2_number, Int_t& pt_max1_number, Int_t& pt_max2_number, Float_t trigger, TLorentzVector& Bjet1,TLorentzVector& Bjet2, TLorentzVector& Qjet1, TLorentzVector& Qjet2,TLorentzVector& qq, Float_t scale=1.){
	int not_pass=0;

		Float_t btag_max = -100;

		int loopJetmin = 6;
		if (nJets<6) loopJetmin=nJets;

		for (int i=0;i<loopJetmin;i++){
			if ((isnan(Jet_btagCSV[i])==1)||(isinf(Jet_btagCSV[i]==1)) ) Jet_btagCSV[i]=1.; 
			if (Jet_btagCSV[i]>1) Jet_btagCSV[i]=1.;
		}


		for (int i=0;i<loopJetmin;i++){
			if ((Jet_btagCSV[i]>btag_max)/*&&(Jet_id[i]>0)*/){
				btag_max=Jet_btagCSV[i];
				btag_max1_number=i;
			}
		}
		btag_max = -100;
		for (int i=0;i<loopJetmin;i++){
			if ((Jet_btagCSV[i]>btag_max)&&(i!=btag_max1_number)/*&&(Jet_id[i]>0)*/) {
				btag_max=Jet_btagCSV[i];
				btag_max2_number=i;
			} 
		}

		if (!((btag_max1_number>=0)&&(btag_max2_number>=0))) return -1;
		Bjet1.SetPtEtaPhiM(Jet_pt[btag_max1_number],Jet_eta[btag_max1_number],Jet_phi[btag_max1_number],Jet_mass[btag_max1_number]);
		
		Bjet2.SetPtEtaPhiM(Jet_pt[btag_max2_number],Jet_eta[btag_max2_number],Jet_phi[btag_max2_number],Jet_mass[btag_max2_number]);


		Float_t pt_max = 20.*scale;
		for (int i=0;i<loopJetmin;i++){
			if ((Jet_pt[i]>pt_max)&&(i!=btag_max1_number)&&(i!=btag_max2_number)/*&&(Jet_id[i]>0)*/) {
				pt_max=Jet_pt[i];
				pt_max1_number=i;	
			}
		}
		pt_max = 20.*scale;
		for (int i=0;i<loopJetmin;i++){
			if ((Jet_pt[i]>pt_max)&&(i!=btag_max1_number)&&(i!=btag_max2_number)&&(i!=pt_max1_number)/*&&(Jet_id[i]>0)*/) {
				pt_max=Jet_pt[i];
				pt_max2_number=i;	
			}
		}
		
		if (!((pt_max1_number>=0)&&(pt_max2_number>=0))) return -1;
			
		Qjet1.SetPtEtaPhiM(Jet_pt[pt_max1_number],Jet_eta[pt_max1_number],Jet_phi[pt_max1_number],Jet_mass[pt_max1_number]);
		
		Qjet2.SetPtEtaPhiM(Jet_pt[pt_max2_number],Jet_eta[pt_max2_number],Jet_phi[pt_max2_number],Jet_mass[pt_max2_number]);


		qq = Qjet1+Qjet2;
	
	return not_pass;
}
