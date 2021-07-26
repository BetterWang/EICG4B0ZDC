
struct ZDCB0plot {
    TH2D * h2DXY = 0;
    TH2D * h2DXZ = 0;
    TH2D * h2DYZ = 0;
    TH1D * hEtot = 0;

    ZDCB0plot(TFile *f) {
        h2DXY = (TH2D*) f->Get("h2DXY");
        h2DXZ = (TH2D*) f->Get("h2DXZ");
        h2DYZ = (TH2D*) f->Get("h2DYZ");
        hEtot = (TH1D*) f->Get("hEtot");
    }
    void MakePlot(string s) {
        gStyle->SetOptStat(1101);
        TCanvas c1("c1", "c1", 800, 600);
        c1.SetLogz();
        h2DXY->Draw("colz");
        c1.SaveAs( (s+"_XY.pdf").c_str() );
        h2DXZ->Draw("colz");
        c1.SaveAs( (s+"_XZ.pdf").c_str() );
        h2DYZ->Draw("colz");
        c1.SaveAs( (s+"_YZ.pdf").c_str() );
        hEtot->Draw();
        c1.SetLogy();
        c1.SetLogz(0);
        c1.SaveAs( (s+"_E.pdf").c_str() );
    }
};

void plot()
{
    gStyle->SetOptStat(1111);
    TFile * fZDC100MeV = new TFile("output_ZDCB0_gamma_100MeV.root");
    TFile * fZDC300MeV = new TFile("output_ZDCB0_gamma_300MeV.root");
    TFile * fZDC500MeV = new TFile("output_ZDCB0_gamma_500MeV.root");
    TFile * fZDC1GeV   = new TFile("output_ZDCB0_gamma_1GeV.root");
    TFile * fZDC3GeV   = new TFile("output_ZDCB0_gamma_3GeV.root");
    TFile * fZDC5GeV   = new TFile("output_ZDCB0_gamma_5GeV.root");
    TFile * fZDC10GeV  = new TFile("output_ZDCB0_gamma_10GeV.root");

    ZDCB0plot zdc100MeV(fZDC100MeV);
    ZDCB0plot zdc300MeV(fZDC300MeV);
    ZDCB0plot zdc500MeV(fZDC500MeV);
    ZDCB0plot zdc1GeV(fZDC1GeV);
    ZDCB0plot zdc3GeV(fZDC3GeV);
    ZDCB0plot zdc5GeV(fZDC5GeV);
    ZDCB0plot zdc10GeV(fZDC10GeV);

    zdc100MeV.MakePlot("out100MeV");
    zdc300MeV.MakePlot("out300MeV");
    zdc500MeV.MakePlot("out500MeV");
    zdc1GeV.MakePlot("out1GeV");
    zdc3GeV.MakePlot("out3GeV");
    zdc5GeV.MakePlot("out5GeV");
    zdc10GeV.MakePlot("out10GeV");

}
