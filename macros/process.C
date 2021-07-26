#include <vector>
#include <iostream>
#include "TFile.h"
#include "TTree.h"

#include "TH1D.h"
#include "TH2D.h"
#include "TStyle.h"

extern TStyle* gStyle;

void process(string fname = "ZDCB0_gamma_100MeV.root", double E = 100.)
{
    gStyle->SetOptStat(1111);
    using namespace std;

    TFile* f = new TFile(fname.c_str());
    TTree* trV = (TTree*) f->Get("zdchit");

    Int_t           Nhit;
    vector<int>     *layerType = 0;
    vector<int>     *layerID = 0;
    vector<int>     *xID = 0;
    vector<int>     *yID = 0;
    vector<float>   *x0 = 0;
    vector<float>   *y0 = 0;
    vector<float>   *z0 = 0;
    vector<float>   *x1 = 0;
    vector<float>   *y1 = 0;
    vector<float>   *z1 = 0;
    vector<float>   *time0 = 0;
    vector<float>   *time1 = 0;
    vector<float>   *edep = 0;

    trV->SetBranchAddress("Nhit", &Nhit);
    trV->SetBranchAddress("layerType", &layerType);
    trV->SetBranchAddress("layerID", &layerID);
    trV->SetBranchAddress("xID", &xID);
    trV->SetBranchAddress("yID", &yID);
    trV->SetBranchAddress("x0", &x0);
    trV->SetBranchAddress("y0", &y0);
    trV->SetBranchAddress("z0", &z0);
    trV->SetBranchAddress("x1", &x1);
    trV->SetBranchAddress("y1", &y1);
    trV->SetBranchAddress("z1", &z1);
    trV->SetBranchAddress("time0", &time0);
    trV->SetBranchAddress("time1", &time1);
    trV->SetBranchAddress("edep", &edep);

    TH2D * h2DXY = new TH2D("h2DXY", "h2DXY;X(cm);Y(cm)", 400, -20., 20., 400, -20., 20.);
    TH2D * h2DXZ = new TH2D("h2DXZ", "h2DXZ;X(cm);Z(cm)", 400, -20., 20., 100, -5., 5.);
    TH2D * h2DYZ = new TH2D("h2DYZ", "h2DYZ;Y(cm);Z(cm)", 400, -20., 20., 100, -5., 5.);
    TH1D * hEtot = new TH1D("hEtot", "hEtot;E/Etot", 11, 0, 1.1);

    unsigned int Nevt = trV->GetEntries();
    unsigned int ievt = 0;
    while (trV->GetEntry(ievt++)) {
        cout << " !!! ievt = " << ievt << endl;
        double Etot = 0.;
        for ( int i = 0; i < Nhit; i++ ) {
            h2DXY->Fill( (*x0)[i], (*y0)[i], (*edep)[i] );
            h2DXZ->Fill( (*x0)[i], (*z0)[i], (*edep)[i] );
            h2DYZ->Fill( (*y0)[i], (*z0)[i], (*edep)[i] );
            Etot += (*edep)[i];
        }
        hEtot->Fill(Etot/E);
    }

    h2DXY->Scale(1./Nevt);
    h2DXZ->Scale(1./Nevt);
    h2DYZ->Scale(1./Nevt);
    hEtot->Scale(1./Nevt);

    TFile* fsave = new TFile( (string("output_")+fname).c_str(), "recreate" );
    h2DXY->Write();
    h2DXZ->Write();
    h2DYZ->Write();
    hEtot->Write();
}
