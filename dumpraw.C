// -*- mode: c++; c-basic-offset: 4; indent-tabs-mode: nil -*-

#include <iostream>
#include <iomanip>
#include <stdio.h>

void dumpraw (TString source = "/Users/tom/alice/data/2018/LHC18r/000296934/raw/18000296934039.915.root")
{
  AliRawReader* reader = NULL;

  if (source.Contains(".root")) {

    cout << "[I] Reading with ROOT" << endl;
    AliRawReaderRoot *readerDate = new AliRawReaderRoot(source);
    readerDate->SelectEquipment(0, 1024, 1024);
    readerDate->Select("TRD");
    //readerDate->SelectEvents(7);
    reader = (AliRawReader*)readerDate;

  } else if (source.Contains(":")) {

    cout << "[I] Reading DATE monitoring events" << endl;
    AliRawReaderDateOnline *readerRoot = new AliRawReaderDateOnline(source);
    readerRoot->SelectEquipment(0, 1024, 1041);
    readerRoot->Select("TRD");
    //readerRoot->SelectEvents(7);
    reader = (AliRawReader*)readerRoot;
  }

  int ievent = 0;
  while (reader->NextEvent()) {
    ievent++;
    if (ievent > 3) {
      cout << "Reading finished, start drawing..." << endl;
      break;
    }

    cout << "# Event " << ievent << endl;

    UChar_t *buffer = 0x0;

    while (reader->ReadNextData(buffer)) {

      cout << "  # Equipment: " << reader->GetEquipmentId() << endl;

      UInt_t *data = (UInt_t*) buffer;

      char fname[20];
      sprintf(fname, "ev%05d.%04d.raw",ievent,reader->GetEquipmentId());
      cout << fname << endl;
      int fd=open(fname, O_WRONLY|O_CREAT|O_TRUNC, 0644);
      cout << fd << endl;
      perror(NULL);
      write(fd,buffer,reader->GetDataSize());
      close(fd);

      for (int i=0; i<reader->GetDataSize(); i++) {
        // cout << i << ": " << hex << setw(8) << data[i] << endl;
      }
    }

  } //while event


  if (reader) delete reader;

}
