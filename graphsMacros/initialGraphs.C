void setStyle()
{
	gROOT->SetStyle("Plain");
	gStyle->SetPalette(57);
	gStyle->SetOptTitle(0);
}

void grafico()
{
	TF1* graphY = new TF1("graphY", "TMath::Gaus(y, 0.1, 1.0)", -4.0, 4.0);
	TF1* graphTheta = new TF1("graphTheta", "TMath::Gaus(t, 0.1, 0.5)", -3.14 / 2 / 2, 3.14 / 2);

	TCanvas* cInitialGraphs = new TCanvas("cInitialGraphs", "Gaussiane distribuzioni iniziali", 10, 30, 1000, 600);
	cInitialGraphs->Divide(2, 1);

	cInitialGraphs->cd(1);
	graphY->SetTitle("; y; G(y)");
	graphY->SetMarkerStyle(6);
	graphY->SetLineColor(2);
	graphY->Draw();

	cInitialGraphs->cd(2);
	graphTheta->SetTitle("; theta; G(theta)");
	graphTheta->SetMarkerStyle(6);
	graphTheta->SetLineColor(2);
	graphTheta->Draw();

	cInitialGraphs->Print("cInitialGraphs.pdf");
}