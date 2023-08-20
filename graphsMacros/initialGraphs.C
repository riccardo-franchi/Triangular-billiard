void setStyle()
{
	gROOT->SetStyle("Plain");
	gStyle->SetPalette(57);
	gStyle->SetOptTitle(0);
}

void macha()
{
	TH1F* h1 = new TH1F("h1", "Distribuzione di y_i", 1000, -5, 5);
	TH1F* h2 = new TH1F("h2", "Distribuzione di theta_i", 1000, -5, 5);

	double y;
	double theta;

	fstream file;
	file.open("InitParts.txt", ios::in);

	while (1)
	{
		file >> y >> theta;
		if (file.eof())
			break;
		h1->Fill(y);
		h2->Fill(theta);
	}

	TCanvas* cInitialGraphs = new TCanvas("cInitialGraphs", "Gaussiane distribuzioni iniziali", 10, 30, 1000, 600);
	cInitialGraphs->Divide(2, 1);

	cInitialGraphs->cd(1);
	h1->SetTitle("; y; G(y)");
	h1->SetMarkerStyle(6);
	h1->SetLineColor(2);
	h1->Draw();

	cInitialGraphs->cd(2);
	h2->SetTitle("; theta; G(theta)");
	h2->SetMarkerStyle(6);
	h2->SetLineColor(2);
	h2->Draw();

	cInitialGraphs->Print("cInitialGraphs.pdf");
}