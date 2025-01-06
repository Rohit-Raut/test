//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
////////////////////////////////////////////////////////////////////////////////
//
//  GEANT4 Class source file
//
//  G4RadioactiveDecay
//
//  Author: R.Raut
//  Date: 3 Jan 2025  
//
//
////////////////////////////////////////////////////////////////////////////////


#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "QGSP_BERT.hh"
#include "include/DetectorConstruction.hh"
#include "include/PhysicsList.hh"
#include "include/PrimaryGeneratorAction.hh"
#include "include/EventAction.hh"
#include "include/HistoManager.hh"

int main(int argc, char** argv)
{
    G4RunManager* runManager = new G4RunManager;
    runManager->SetUserInitialization(new DetectorConstruction);
    runManager->SetUserInitialization(new PhysicsList);
    //runManager->SetUserInitialization(new QGSP_BERT);
    runManager->SetUserAction(new PrimaryGeneratorAction);

    HistoManager* histo = new HistoManager;
    histo->OpenFile("myOutputFile");
    auto eventAction = new EventAction(histo);
    runManager->SetUserAction(eventAction);

    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialize();

    G4UIExecutive* ui = new G4UIExecutive(argc, argv);
    G4UImanager* UImanager = G4UImanager::GetUIpointer();
    UImanager->ApplyCommand("/control/execute /Users/rohit/Research/Bismuth_sim/Purity_Geant4/vis.mac");
    ui->SessionStart();
    histo->Save();
    delete histo;
    delete ui;
    delete visManager;
    delete runManager;
    return 0;
}