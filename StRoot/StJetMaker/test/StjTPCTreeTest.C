// Copyright (C) 2008 Tai Sakuma <sakuma@bnl.gov>
#include <StjTPCTree.h>
#include "StjTPCTreeTest.hh"

#include <StjTreeEntryCoordinator.h>
#include <StjTreeIndexList.h>

#include <StjTrackListReader.h>

#include <TFile.h>
#include <TTree.h>

#include <iostream>

using namespace std;

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( StjTPCTreeTest );

void StjTPCTreeTest::setUp()
{

}

void StjTPCTreeTest::tearDown()
{

}

void StjTPCTreeTest::testGetEntry() 
{
  TFile* file = new TFile("./part_run6143024.root");

  TTree *tree = dynamic_cast<TTree*>(file->Get("tpcTracks"));

  StjTrackListReader *reader = new StjTrackListReader(tree);

  tree->BuildIndex("runNumber", "eventId");

  reader->Init();

  StjTPCTree* tpc = new StjTPCTree(reader);

  reader->GetEntryWithIndex(6143024, 38);

  StjTrackList trackList = tpc->getTrackList();
  CPPUNIT_ASSERT_EQUAL( (size_t)13, trackList.size() );
  CPPUNIT_ASSERT_EQUAL((Short_t) 87, trackList[0].id );
  CPPUNIT_ASSERT_EQUAL((Short_t) 80, trackList[1].id );
  CPPUNIT_ASSERT_EQUAL((Short_t) 77, trackList[2].id );
  CPPUNIT_ASSERT_EQUAL((Short_t) 76, trackList[3].id );
  CPPUNIT_ASSERT_EQUAL((Short_t) 67, trackList[4].id );
  CPPUNIT_ASSERT_EQUAL((Short_t) 65, trackList[5].id );
  CPPUNIT_ASSERT_EQUAL((Short_t) 51, trackList[6].id );
  CPPUNIT_ASSERT_EQUAL((Short_t) 29, trackList[7].id );
  CPPUNIT_ASSERT_EQUAL((Short_t) 11, trackList[8].id );
  CPPUNIT_ASSERT_EQUAL((Short_t)199, trackList[9].id );
  CPPUNIT_ASSERT_EQUAL((Short_t)192, trackList[10].id );
  CPPUNIT_ASSERT_EQUAL((Short_t)185, trackList[11].id );
  CPPUNIT_ASSERT_EQUAL((Short_t)181, trackList[12].id );

  
  reader->GetEntryWithIndex(6143024, 41);
  trackList = tpc->getTrackList();
  CPPUNIT_ASSERT_EQUAL( (size_t)0, trackList.size() );

  delete tpc;
  delete file;
}

