void setStyle()
{
	gROOT->SetStyle("Plain");
	gStyle->SetPalette(57);
	gStyle->SetOptTitle(0);
}

void machaInitial()
{
	TH1F* h1 = new TH1F("h1", "Distribuzione di y_i", 1000, -200, 200);
	TH1F* h2 = new TH1F("h2", "Distribuzione di theta_i", 1000, -TMath::PiOver2(), TMath::PiOver2());

	double y;
	double theta;

	fstream file;
	file.open("initial11.txt", ios::in);

	while (1)
	{
		file >> y >> theta;
		if (file.eof())
			break;
		h1->Fill(y);
		h2->Fill(theta);
	}

	TCanvas* cInitialGraphs = new TCanvas("cGraphs4", "Distribuzioni iniziali di y e theta", 10, 30, 1000, 600);
	cInitialGraphs->Divide(2, 1);

	cInitialGraphs->cd(1);
	h1->SetTitle("Distribuzione di y_{i}; y; Occorrenze");
	h1->SetMarkerStyle(6);
	h1->SetLineColor(8);
	h1->Draw();

	cInitialGraphs->cd(2);
	h2->SetTitle("Distribuzione di #theta_{i}; #theta (rad); Occorrenze");
	h2->SetMarkerStyle(6);
	h2->SetLineColor(9);
	h2->Draw();

	cInitialGraphs->Print("cHistosInit11.pdf");
}

void machaFinal()
{
	TH1F* h1 = new TH1F("h1", "Distribuzione di y_f", 1000, -15, 15);
	TH1F* h2 = new TH1F("h2", "Distribuzione di theta_f", 1000, -TMath::PiOver2(), TMath::PiOver2());

	double y;
	double theta;

	fstream file;
	file.open("simulation11.txt", ios::in);

	while (1)
	{
		file >> y >> theta;
		if (file.eof())
			break;
		h1->Fill(y);
		h2->Fill(theta);
	}

	TCanvas* cFinalGraphs = new TCanvas("cGraphs3", "Distribuzioni finali di y e theta", 10, 30, 1000, 600);
	cFinalGraphs->Divide(2, 1);

	cFinalGraphs->cd(1);
	h1->SetTitle("Distribuzione di y_{f}; y; Occorrenze");
	h1->SetMarkerStyle(6);
	h1->SetLineColor(8);
	h1->Draw();

	cFinalGraphs->cd(2);
	h2->SetTitle("Distribuzione di #theta_{f}; #theta (rad); Occorrenze");
	h2->SetMarkerStyle(6);
	h2->SetLineColor(9);
	h2->Draw();

	cFinalGraphs->Print("cHistosFin11.pdf");
}