
#include "Headers/RAWDataHeader.h"
#include <iomanip>

using namespace std;

struct trd_cru_header{
  union {
    // default value
    uint64_t word0 = 0x0;
    struct {
      uint64_t event_type : 8;        /// bit  0 to  7: header version
      uint64_t stop_bits : 4;     /// bit  8 to 15: header size
      uint64_t bc_id : 12;         /// bit 16 to 31: FEE identifier
      uint64_t header_version : 8;       /// bit 32 to 39: priority bit
      uint64_t res0 : 32;                /// bit 40 to 63: zeroed
    };                             ///
  };
};

void show_buffer(char* buf)
{
  uint64_t* buf64 = (uint64_t*)buf;
  cout << "=============" << endl;
  for (int i=0; i<8;i++) {
    cout << setw(16) << buf64[i] << endl;
  }
  cout << "-------------" << endl;
  for (int i=8; i<20;i++) {
    cout << setw(16) << buf64[i] << endl;
  }
}

void fakerdh()
{
  cout << hex << setfill('0') << endl;

  // open output file handle
  int ofh = open("data.o2raw",O_WRONLY|O_CREAT|O_TRUNC, 00644);

  char buffer[8192];
  // show_buffer(buffer);

  // create the RDH
  o2::header::RAWDataHeaderV5 *rdh = new(buffer) o2::header::RAWDataHeaderV5;
  // show_buffer(buffer);


  // set some stuff
  rdh->feeId = 42;
  show_buffer(buffer);


  trd_cru_header *trdhdr = new(buffer+sizeof(o2::header::RAWDataHeaderV5)) trd_cru_header;
  trdhdr->event_type = 13;
  show_buffer(buffer);



  char *payload = buffer+sizeof(o2::header::RAWDataHeaderV5)+sizeof(trd_cru_header);
  payload[0] = 0xEF;
  payload[1] = 0xBE;
  payload[2] = 0xAD;
  payload[3] = 0xDE;

  show_buffer(buffer);

  // write everything to the file
  write(ofh,payload,8192);


  // close the output file
  close(ofh);


}
