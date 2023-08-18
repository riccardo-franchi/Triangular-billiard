void setStyle(){
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(57);
  gStyle->SetOptTitle(0);
}

void grafico() {
TGraphErrors *graph1 = new TGraphErrors ("firstSimulation.txt", "%lg %lg %*lg %*lg %*lg");
TGraphErrors *graph2 = new TGraphErrors ("firstSimulation.txt", "%lg %*lg %lg %*lg %*lg");
TGraphErrors *graph3 = new TGraphErrors ("firstSimulation.txt", "%lg %*lg %*lg %lg %*lg");
TGraphErrors *graph4 = new TGraphErrors ("firstSimulation.txt", "%lg %*lg %*lg %*lg %lg");

  TCanvas *cGraphs = new TCanvas("cGraphs", "Dipendenza dei parametri da l",10,30,1000,600);
  cGraphs->Divide(2,2);
  
  cGraphs->cd(1);
  graph1->SetTitle("; l; Media y_f");
  graph1->SetMarkerStyle(4);
  graph1->SetLineColor(2);
  graph1->Draw();
 
  cGraphs->cd(2);
  graph2->SetTitle("; l; Dev. st. y_f");
  graph2->SetMarkerStyle(6);
  graph2->SetLineColor(2);
  graph2->Draw();
 
  cGraphs->cd(3);
  graph3->SetTitle("; l; Media theta_f");
  graph3->SetMarkerStyle(4);
  graph3->SetLineColor(2);
  graph3->Draw();
  
  cGraphs->cd(4);
  graph4->SetTitle("; l; Dev. st. theta_f");
  graph4->SetMarkerStyle(6);
  graph4->SetLineColor(2);
  graph4->Draw();

  cGraphs->Print("cGraphs.pdf");
}
