{

  bool passingMVATightNew2 = 
    (( abs(el_eta) < 0.8 && el_pt >=10 && el_pt < 25 && el_MVA94Xnoiso > (0.2 + (0.032)*(el_pt-10.))) ||
     ( abs(el_eta) < 0.8 && el_pt >= 25 && el_MVA94Xnoiso > 0.68) ||
     
     ( abs(el_eta) >= 0.8 && abs(el_eta) < 1.479 && el_pt >=10 && el_pt < 25 && el_MVA94Xnoiso > (0.1 + (0.025)*(el_pt-10.))) ||
     ( abs(el_eta) >= 0.8 && abs(el_eta) < 1.479 && el_pt >= 25 && el_MVA94Xnoiso > 0.475) ||
     
     ( abs(el_eta) >= 1.479 && abs(el_eta) < 2.4 && el_pt >=10 && el_pt < 25 && el_MVA94Xnoiso > (-0.1 + (0.028)*(el_pt-10.))) ||
     ( abs(el_eta) >= 1.479 && abs(el_eta) < 2.4 && el_pt >= 25 && el_MVA94Xnoiso > 0.32));
  
  bool passingMVALoose =
    (( abs(el_eta) < 0.8 && el_pt >=5 && el_pt < 10 && el_MVA94Xnoiso > (0.488)) ||
     ( abs(el_eta) < 0.8 && el_pt >=10 && el_pt < 25 && el_MVA94Xnoiso > (-0.788 + (0.148/15.)*(el_pt-10.))) ||
     ( abs(el_eta) < 0.8 && el_pt >= 25 && el_MVA94Xnoiso > -0.640) ||
     
     ( abs(el_eta) >= 0.8 && abs(el_eta) < 1.479 && el_pt >=5 && el_pt < 10 && el_MVA94Xnoiso > (-0.045)) ||
     ( abs(el_eta) >= 0.8 && abs(el_eta) < 1.479 && el_pt >=10 && el_pt < 25 && el_MVA94Xnoiso > (-0.850 + (0.075/15.)*(el_pt-10.))) ||
     ( abs(el_eta) >= 0.8 && abs(el_eta) < 1.479 && el_pt >= 25 && el_MVA94Xnoiso > -0.775) ||
     
     ( abs(el_eta) >= 1.479 && abs(el_eta) < 2.4 && el_pt >=5 && el_pt < 10 && el_MVA94Xnoiso > (0.176)) ||
     ( abs(el_eta) >= 1.479 && abs(el_eta) < 2.4 && el_pt >=10 && el_pt < 25 && el_MVA94Xnoiso > (-0.81 + (0.077/15.)*(el_pt-10.))) ||
     ( abs(el_eta) >= 1.479 && abs(el_eta) < 2.4 && el_pt >= 25 && el_MVA94Xnoiso > -0.733));

  bool passingMVALooseFO =
    (( abs(el_eta) < 0.8 && el_pt >=5 && el_pt < 10 && el_MVA94Xnoiso > (-0.135)) ||
     ( abs(el_eta) < 0.8 && el_pt >=10 && el_pt < 25 && el_MVA94Xnoiso > (-0.930 + (0.043/15.)*(el_pt-10.))) ||
     ( abs(el_eta) < 0.8 && el_pt >= 25 && el_MVA94Xnoiso > -0.887) ||
     
     ( abs(el_eta) >= 0.8 && abs(el_eta) < 1.479 && el_pt >=5 && el_pt < 10 && el_MVA94Xnoiso > (-0.417)) ||
     ( abs(el_eta) >= 0.8 && abs(el_eta) < 1.479 && el_pt >=10 && el_pt < 25 && el_MVA94Xnoiso > (-0.93 + (0.04/15.)*(el_pt-10.))) ||
     ( abs(el_eta) >= 0.8 && abs(el_eta) < 1.479 && el_pt >= 25 && el_MVA94Xnoiso > -0.890) ||
     
     ( abs(el_eta) >= 1.479 && abs(el_eta) < 2.4 && el_pt >=5 && el_pt < 10 && el_MVA94Xnoiso > (-0.470)) ||
     ( abs(el_eta) >= 1.479 && abs(el_eta) < 2.4 && el_pt >=10 && el_pt < 25 && el_MVA94Xnoiso > (-0.942 + (0.032/15.)*(el_pt-10.))) ||
     ( abs(el_eta) >= 1.479 && abs(el_eta) < 2.4 && el_pt >= 25 && el_MVA94Xnoiso > -0.910));

}
