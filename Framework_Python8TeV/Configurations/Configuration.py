Job = {
    "Batch"           : True,
    "Analysis"        : "TTbarAnalysis",
    "Fraction"        : 1,
    "MaxEvents"       : 1234567890,
    "OutputDirectory" : "results/"
}

prefix = "/home/atlas-open-data/8tev/"
#VBSAnalysis

Processes = {
  # Diboson processes
  "WW"                    : prefix+"MC/mc_105985.WW.root",
  "ZZ"                    : prefix+"MC/mc_105986.ZZ.root",
  "WZ"                    : prefix+"MC/mc_105987.WZ.root",

  # single top processes
  "stop_tchan_top"        : prefix+"MC/mc_110090.stop_tchan_top.root",
  "stop_tchan_antitop"    : prefix+"MC/mc_110091.stop_tchan_antitop.root",
  "stop_schan"            : prefix+"MC/mc_110119.stop_schan.root",
  "stop_wtchan"           : prefix+"MC/mc_110140.stop_wtchan.root",

  # top pair processes
  "ttbar_had"             : prefix+"MC/mc_117049.ttbar_had.root",
  "ttbar_lep"             : prefix+"MC/mc_117050.ttbar_lep.root",

  # Z+jets processes
  "Zee"                   : prefix+"MC/mc_147770.Zee.root",
  "Zmumu"                 : prefix+"MC/mc_147771.Zmumu.root",
  "Ztautau"               : prefix+"MC/mc_147772.Ztautau.root",

  # Low Mass Z+jets processes
  "DYeeM08to15"           : prefix+"MC/mc_173041.DYeeM08to15.root",
  "DYeeM15to40"           : prefix+"MC/mc_173042.DYeeM15to40.root",
  "DYmumuM08to15"         : prefix+"MC/mc_173043.DYmumuM08to15.root",
  "DYmumuM15to40"         : prefix+"MC/mc_173044.DYmumuM15to40.root",
  "DYtautauM08to15"       : prefix+"MC/mc_173045.DYtautauM08to15.root",
  "DYtautauM15to40"       : prefix+"MC/mc_173046.DYtautauM15to40.root",

  # W+jets processes
  "WenuWithB"             : prefix+"MC/mc_167740.WenuWithB.root",
  "WenuJetsBVeto"         : prefix+"MC/mc_167741.WenuJetsBVeto.root",
  "WenuNoJetsBVeto"       : prefix+"MC/mc_167742.WenuNoJetsBVeto.root",
  "WmunuWithB"            : prefix+"MC/mc_167743.WmunuWithB.root",
  "WmunuJetsBVeto"        : prefix+"MC/mc_167744.WmunuJetsBVeto.root",
  "WmunuNoJetsBVeto"      : prefix+"MC/mc_167745.WmunuNoJetsBVeto.root",
  "WtaunuWithB"           : prefix+"MC/mc_167746.WtaunuWithB.root",
  "WtaunuJetsBVeto"       : prefix+"MC/mc_167747.WtaunuJetsBVeto.root",
  "WtaunuNoJetsBVeto"     : prefix+"MC/mc_167748.WtaunuNoJetsBVeto.root",

  # Higgs Processes
  "ggH125_ZZ4lep"         : prefix+"MC/mc_160155.ggH125_ZZ4lep.root",
  "VBFH125_ZZ4lep"        : prefix+"MC/mc_160205.VBFH125_ZZ4lep.root",
  "ggH125_WW2lep"         : prefix+"MC/mc_161005.ggH125_WW2lep.root",
  "VBFH125_WW2lep"        : prefix+"MC/mc_161055.VBFH125_WW2lep.root",

  # ZPrime Processes
  "ZPrime400"             : prefix+"MC/mc_110899.ZPrime400.root",
  "ZPrime500"             : prefix+"MC/mc_110901.ZPrime500.root",
  "ZPrime750"             : prefix+"MC/mc_110902.ZPrime750.root",
  "ZPrime1000"            : prefix+"MC/mc_110903.ZPrime1000.root",
  "ZPrime1250"            : prefix+"MC/mc_110904.ZPrime1250.root",
  "ZPrime1500"            : prefix+"MC/mc_110905.ZPrime1500.root",
  "ZPrime1750"            : prefix+"MC/mc_110906.ZPrime1750.root",
  "ZPrime2000"            : prefix+"MC/mc_110907.ZPrime2000.root",
  "ZPrime2250"            : prefix+"MC/mc_110908.ZPrime2250.root",
  "ZPrime2500"            : prefix+"MC/mc_110909.ZPrime2500.root",
  "ZPrime3000"            : prefix+"MC/mc_110910.ZPrime3000.root",

  # Data
  "data_Egamma"           : prefix+"Data/DataEgamma*.root",
  "data_Muons"            : prefix+"Data/DataMuons*.root",
}
