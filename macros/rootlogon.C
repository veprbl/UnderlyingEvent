void rootlogon()
{
   const char *star_path = gSystem->Getenv("STAR");
   // For ACLiC mode
   gSystem->AddIncludePath(Form(" -I%s/StRoot ", star_path));
   gSystem->AddLinkedLibs(Form(" -L%s/.sl64_gcc482/lib -lStJetEvent -lStJetSkimEvent ", star_path));
   // For macro mode
   gROOT->ProcessLine(Form(".include %s/StRoot", star_path));
   gSystem->Load("StJetEvent");
   gSystem->Load("StJetSkimEvent");
}
