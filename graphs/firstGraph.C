void setStyle()
{
	gROOT->SetStyle("Plain");
	gStyle->SetPalette(57);
	gStyle->SetOptTitle(0);
}

void grafico()
{
	TGraphErrors* graph1 = new TGraphErrors("firstSimulation.txt", "%lg %lg %*lg %*lg %*lg %*lg %*lg %*lg %*lg");
	TGraphErrors* graph2 = new TGraphErrors("firstSimulation.txt", "%lg %*lg %lg %*lg %*lg %*lg %*lg %*lg %*lg");
	TGraphErrors* graph3 = new TGraphErrors("firstSimulation.txt", "%lg %*lg %*lg %lg %*lg %*lg %*lg %*lg %*lg");
	TGraphErrors* graph4 = new TGraphErrors("firstSimulation.txt", "%lg %*lg %*lg %*lg %lg %*lg %*lg %*lg %*lg");
	TGraphErrors* graph5 = new TGraphErrors("firstSimulation.txt", "%lg %*lg %*lg %*lg %*lg %lg %*lg %*lg %*lg");
	TGraphErrors* graph6 = new TGraphErrors("firstSimulation.txt", "%lg %*lg %*lg %*lg %*lg %*lg %lg %*lg %*lg");
	TGraphErrors* graph7 = new TGraphErrors("firstSimulation.txt", "%lg %*lg %*lg %*lg %*lg %*lg %*lg %lg %*lg");
	// TGraphErrors* graph8 = new TGraphErrors("firstSimulation.txt", "%lg %*lg %*lg %*lg %*lg %*lg %*lg %*lg %lg");

	TCanvas* cGraphsA = new TCanvas("cGraphsA", "Dipendenza dei parametri da l", 10, 30, 1000, 600);
	cGraphs->Divide(2, 2);

	cGraphsA->cd(1);
	graph1->SetTitle("; l; Media y_f");
	graph1->SetMarkerStyle(4);
	graph1->SetLineColor(2);
	graph1->Draw();

	cGraphsA->cd(2);
	graph2->SetTitle("; l; Dev. st. y_f");
	graph2->SetMarkerStyle(6);
	graph2->SetLineColor(2);
	graph2->Draw();

	cGraphsA->cd(3);
	graph3->SetTitle("; l; Media theta_f");
	graph3->SetMarkerStyle(4);
	graph3->SetLineColor(2);
	graph3->Draw();

	cGraphsA->cd(4);
	graph4->SetTitle("; l; Dev. st. theta_f");
	graph4->SetMarkerStyle(6);
	graph4->SetLineColor(2);
	graph4->Draw();

	cGraphsA->Print("cGraphsA.pdf");

	TCanvas* cGraphsB = new TCanvas("cGraphsB", "Dipendenza dei parametri da l", 10, 30, 1000, 600);
	cGraphs->Divide(2, 1);

	cGraphsB->cd(1);
	graph5->SetTitle("; l; Media y_f");
	graph5->SetMarkerStyle(4);
	graph5->SetLineColor(2);
	graph5->Draw();

	cGraphsB->cd(2);
	graph6->SetTitle("; l; Dev. st. y_f");
	graph6->SetMarkerStyle(6);
	graph6->SetLineColor(2);
	graph6->Draw();

	cGraphsB->cd(3);
	graph7->SetTitle("; l; Media theta_f");
	graph7->SetMarkerStyle(4);
	graph7->SetLineColor(2);
	graph7->Draw();
	/*
		cGraphsA->cd(4);
		graph4->SetTitle("; l; Dev. st. theta_f");
		graph4->SetMarkerStyle(6);
		graph4->SetLineColor(2);
		graph4->Draw();
	*/
	cGraphsA->Print("cGraphsA.pdf");
}
