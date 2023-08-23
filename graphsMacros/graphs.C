void setStyle()
{
	gROOT->SetStyle("Plain");
	gStyle->SetPalette(57);
	gStyle->SetOptTitle(0);
}

void grafico()
{
	TGraphErrors* graph1 = new TGraphErrors("simulation5.txt", "%lg %lg %*lg %*lg %*lg %*lg %*lg %*lg %*lg %*lg");
	TGraphErrors* graph2 = new TGraphErrors("simulation5.txt", "%lg %*lg %lg %*lg %*lg %*lg %*lg %*lg %*lg %*lg");
	TGraphErrors* graph3 = new TGraphErrors("simulation5.txt", "%lg %*lg %*lg %lg %*lg %*lg %*lg %*lg %*lg %*lg");
	TGraphErrors* graph4 = new TGraphErrors("simulation5.txt", "%lg %*lg %*lg %*lg %lg %*lg %*lg %*lg %*lg %*lg");
	TGraphErrors* graph5 = new TGraphErrors("simulation5.txt", "%lg %*lg %*lg %*lg %*lg %lg %*lg %*lg %*lg %*lg");
	TGraphErrors* graph6 = new TGraphErrors("simulation5.txt", "%lg %*lg %*lg %*lg %*lg %*lg %lg %*lg %*lg %*lg");
	TGraphErrors* graph7 = new TGraphErrors("simulation5.txt", "%lg %*lg %*lg %*lg %*lg %*lg %*lg %lg %*lg %*lg");
	TGraphErrors* graph8 = new TGraphErrors("simulation5.txt", "%lg %*lg %*lg %*lg %*lg %*lg %*lg %*lg %lg %*lg");
	TGraphErrors* graph9 = new TGraphErrors("simulation5.txt", "%lg %*lg %*lg %*lg %*lg %*lg %*lg %*lg %*lg %lg");

	TCanvas* cGraphsA = new TCanvas("cGraphsA", "Dipendenza dei parametri da l (r_1 = 2, r_2 = 6)", 10, 30, 1000, 600);
	cGraphsA->Divide(2, 2);

	cGraphsA->cd(1);
	graph1->SetTitle("; l; Media y_f");
	graph1->SetMarkerStyle(6);
	graph1->SetLineColor(2);
	graph1->Draw();

	cGraphsA->cd(2);
	graph2->SetTitle("; l; Dev. st. y_f");
	graph2->SetMarkerStyle(6);
	graph2->SetLineColor(2);
	graph2->Draw();

	cGraphsA->cd(3);
	graph3->SetTitle("; l; Media theta_f");
	graph3->SetMarkerStyle(6);
	graph3->SetLineColor(2);
	graph3->Draw();

	cGraphsA->cd(4);
	graph4->SetTitle("; l; Dev. st. theta_f");
	graph4->SetMarkerStyle(6);
	graph4->SetLineColor(2);
	graph4->Draw();

	cGraphsA->Print("cGraphsA5.pdf");

	TCanvas* cGraphsB = new TCanvas("cGraphsB", "Dipendenza dei parametri da l (r_1 = 2, r_2 = 6)", 10, 30, 1000, 600);
	cGraphsB->Divide(2, 2);

	cGraphsB->cd(1);
	graph5->SetTitle("; l; Coeff. di asimm. y_f");
	graph5->SetMarkerStyle(6);
	graph5->SetLineColor(2);
	graph5->Draw();

	cGraphsB->cd(2);
	graph6->SetTitle("; l; Curtosi y_f");
	graph6->SetMarkerStyle(6);
	graph6->SetLineColor(2);
	graph6->Draw();

	cGraphsB->cd(3);
	graph7->SetTitle("; l; Coeff. di asimm. theta_f");
	graph7->SetMarkerStyle(6);
	graph7->SetLineColor(2);
	graph7->Draw();

	cGraphsB->cd(4);
	graph8->SetTitle("; l; Curtosi theta_f");
	graph8->SetMarkerStyle(6);
	graph8->SetLineColor(2);
	graph8->Draw();

	cGraphsB->Print("cGraphsB5.pdf");

	TCanvas* cGraphC = new TCanvas("cGraphC", "Dipendenza dei parametri da l (r_1 = 2, r_2 = 6)", 10, 30, 1000, 600);
	graph9->SetTitle("; l; Particelle uscite");
	graph9->SetMarkerStyle(6);
	graph9->SetLineColor(2);
	graph9->Draw();

	cGraphC->Print("cGraphsC5.pdf");
}