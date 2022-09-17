// ROOT macro file for plotting example B4 histograms 
// 
// Can be run from ROOT session:
// root[0] .x plotHisto.C
// or in terminal：
// root -l plotHisto.C

#include "TCanvas.h"
#include "TFile.h"
#include "TNtuple.h"
#include "TROOT.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TLegend.h"
#include "TLatex.h"
#include "iostream"
#include "TString.h"
#include <stdio.h>
#include <fstream>
#include <iostream>

using namespace std;



void plotfluxspectrum(){
	
	//==============File name and Data information======================
	
	TString filename="100keV_R5um_5yiTotal_0p5keV.root";
	float targetthickness=5;
	
	TString name1[3]={"FluxSpectrumTotal0","FluxSpectrumTarget0","FluxSpectrumSubstrate0"}; 
	TString name2[3]={"Total","Target","Diamond"}; 
		
	int totalNumSpectrumandEnergy=4;
	int totalNumSpectrum=3;
	int numofbins=202;
	float TmpValue=0;
	
	TString targetthickness_str=Form("%1.0f",targetthickness);//Form,convert int to string in Root.https://www-he.scphys.kyoto-u.ac.jp/member/n-kota/dokuwiki/doku.php?id=ja:root:tstring  
	TString savename = "Flux Spectrum of "+targetthickness_str+"um@100keV";
	TString savefigurename = savename + ".png";
	TString savetxtname = savename + ".txt";	
	
	
	//===========plot the figure========================================	
	
	// Open file filled by Geant4 simulation	 
	TFile *f = TFile::Open(filename);

	// Create a canvas 1
	TCanvas* c1 = new TCanvas("c1", " ", 200, 200, 1000, 1000); 

	
	c1->SetLeftMargin(0.15);
	c1->SetRightMargin(0.15);
	c1->SetTopMargin(0.15);
	c1->SetBottomMargin(0.15);

	c1->SetLogy();
	 
	c1->SetFixedAspectRatio();
	TLegend *legend=new TLegend(.6,.6,.82,.82);
	

	// draw the figure with root method 
    for (int j=0;j<totalNumSpectrum;j++){
		
		TString fluxspectrum = name1[j];
		TH1D *hist = (TH1D*)gDirectory->Get(fluxspectrum);
		
		if ( hist ) hist->Draw("HIST SAME C"); 
		
		hist->SetLineWidth(2);
		hist->SetLineColor(j+1);
		hist->SetStats(0);	
		hist->GetXaxis()->SetTitle("Engery(keV)");
		hist->GetYaxis()->SetTitle("Counts(a.u)");
		hist->GetYaxis()->SetTitleOffset(1.3);
		hist->SetAxisRange(0.5,120,"X");	
		hist->SetTitle(savename);

		TString histname=name2[j];
		
		legend->AddEntry(hist,histname,"l");	
			
	}
	legend->Draw();	


	

	c1->SaveAs(savefigurename);
	
  //hist1->DrawNormalized("HIST SAME C");
  //hist4->DrawNormalized("HIST SAME C");
  //HIST 是一个选项 ref： https://root.cern.ch/root/htmldoc/guides/users-guide/ROOTUsersGuide.html#draw-options	
	
	
	
	
    //=========export the datas to the txt file=========================	
	
	//初始化一个数组， 第一行装位置，后面行依次装不同的数据（"Total","Micro-Structure Target","Diamond-Substrate"）。
	float Countsofeverybin[totalNumSpectrumandEnergy][numofbins];
	for(int i=0;i<totalNumSpectrumandEnergy;i++){
		for(int j=0;j<numofbins;j++){
			Countsofeverybin[i][j]=0;
		}
	}
	//create a matrix for transforming the data 	
	//初始化一个数组， 第一列装位置，后面列依次装不同的层的数据。	
	float MatrixforTransform[numofbins][totalNumSpectrumandEnergy];
	for(int j=0;j<numofbins;j++){
		for(int i=0;i<totalNumSpectrumandEnergy;i++){
			MatrixforTransform[i][j]=0;
		}
	}

	//open the txt file 
	ofstream myFileofSpectrum(savetxtname);	
	
	
    for (int i=0;i<totalNumSpectrum;i++){
		
		TString fluxspectrum = name1[i];
		TH1D *hist = (TH1D*)gDirectory->Get(fluxspectrum);
		//将每个能量箱中的数据输出，如果设置为100个bin,实际的bin的个数是102（设置值+2，i=0对应underflow；i=102对应overflow
		for (int j=0;j<numofbins;j++){
			TmpValue = hist->GetBinContent(j);//->GetXaxis()->GetBinCenter(j);//
			Countsofeverybin[i][j]=TmpValue;
			TmpValue=0;
			TmpValue = hist->GetXaxis()->GetBinCenter(j);//->GetBinContent(j);//
			Countsofeverybin[3][j]=TmpValue;
			TmpValue=0;
		}
	}
    for (int i=0;i<(totalNumSpectrumandEnergy-1);i++){
		
		TString fluxspectrum = name1[i];
		TH1D *hist = (TH1D*)gDirectory->Get(fluxspectrum);
		
		// 打开Total profile的数据，既要存下坐标位置到第0行，还要存下数据到第1行；
		for (int j=0;j<numofbins;j++){
			if (i==0){
				//将每个能量箱中的position输出，如果设置为100个bin,实际的bin的个数是102（设置值+2，i=0对应underflow；i=102对应overflow
				TmpValue = hist->GetXaxis()->GetBinCenter(j);//->GetBinContent(j);//
				Countsofeverybin[i][j]=TmpValue;
				TmpValue=0;
				//将每个能量箱中的data输出，如果设置为100个bin,实际的bin的个数是102（设置值+2，i=0对应underflow；i=102对应overflow
				TmpValue = hist->GetBinContent(j);//->GetXaxis()->GetBinCenter(j);//
				Countsofeverybin[i+1][j]=TmpValue;				
			}
			
			else{
				//将每个能量箱中的data输出，如果设置为100个bin,实际的bin的个数是102（设置值+2，i=0对应underflow；i=102对应overflow
				TmpValue=0;
				TmpValue = hist->GetBinContent(j); //->GetXaxis()->GetBinCenter(j);//
				Countsofeverybin[i+1][j]=TmpValue; //这里用else，上面的if i=0, 这里i是从i=1开始了，所以这里也是i+1,not i+2
				TmpValue=0;
				
			}
		}
	}

	
	// Transform the data for read easily
	for (int i=0;i<totalNumSpectrumandEnergy;i++){
		for (int j=0;j<numofbins;j++){
			MatrixforTransform[j][i] = Countsofeverybin[i][j];
		}
	}

	
	// output the data into txt file	
		for(int i=0;i<numofbins;i++){	
			for (int j=0;j<totalNumSpectrumandEnergy;j++){

				myFileofSpectrum<<MatrixforTransform[i][j]<<" ";
		
		}
		myFileofSpectrum<<endl;	
	}
	
	// close the txt file	
	myFileofSpectrum.close();		

}		

int main(){

    plotfluxspectrum();
    return 0;
}
