/*
 * lvl1_assym.h
 *
 *  Created on: 28.03.2013
 *      Author: kreyl
 */

/*
 * Level 1 of assymetric protocol.
 * Level 1 is responsible to sync rpkt exchange and therefore has
 * high priority.
 */

#ifndef LVL1_ASSYM_H_
#define LVL1_ASSYM_H_

#include "ch.h"
#include "hal.h"
#include "main.h"   // To distinct between concentrator and device
#include "kl_lib_f2xx.h"
#include "kl_buf.h"

// ============================== Pkt_t ========================================
#define RDATA_CNT       17  // Payload data size in single pkt
#define RLASTPKT_DATASZ (RDATA_CNT-1)
struct rPkt_t {
    uint8_t SlotN;      // Number of timeslot
    uint8_t rID;        // Device ID
    uint16_t Srv;       // Service bits
    uint8_t Data[RDATA_CNT];
    int8_t RSSI;        // Received signal level, RX use only
} __attribute__ ((__packed__));
#define RPKT_LEN    (sizeof(rPkt_t)-1)  // Exclude RSSI

// Srv bit masks
#define R_DIR_GATE2DEV  0x8000
#define R_DIR_DEV2GATE  0x0000
// Cmd
#define R_CMD_MASK      0x7000
#define R_CMD_PING      0x0000
#define R_CMD_DATA      0x1000

#define R_NXTSLT        0x0800  // Listen next slot
//#define R_RPIDTX
///#define R_RPIDRX
#define R_ACK           0x0010
//#define R_ACKDYN
//#define R_RPIDDYN

// =========================== Address space ===================================
#define RNO_ID          0   // When device has no ID
// Devices
#define RDEV_BOTTOM_ID  10
#define RDEV_TOP_ID     109
#define RDEVICE_CNT     ((1+RDEV_TOP_ID)-RDEV_BOTTOM_ID)

// Gates
#define RGATE_CNT       7

// Slot count
#define RDYN_SLOT_CNT   0   // Count of dynamic slots
#define RSLOT_CNT       (RDEVICE_CNT + RDYN_SLOT_CNT) // Total slots count
#define ID2SLOT(id)     (id - RDEV_BOTTOM_ID)
#define SLOT2ID(slot)   (slot + RDEV_BOTTOM_ID)

#ifdef DEVICE
#define RNEIGHBOUR_CNT  RGATE_CNT
#else
#define RNEIGHBOUR_CNT  RDEVICE_CNT
#endif

// ============================== Timings ======================================
#define R_TX_WAIT_MS    3   // Measured value of transmission length
#define R_RX_WAIT_MS    4   // How long to wait reply to start
#define RTIMESLOT_MS    (R_TX_WAIT_MS + R_RX_WAIT_MS)   // Length of one timeslot

// Minimum time worth sleeping
#define RMIN_TIME_TO_SLEEP_MS   12
// Start RX this-number-of-timeslots earlier than exact number
#define RRX_START_RESERVE       1

// In sync, try to receive pkt this number of times before returning to alone mode
#define R_IN_SYNC_RETRY_CNT     4

// Time to wait in discovery mode
#define RDISCOVERY_RX_MS        (RTIMESLOT_MS * 2)
#define RDISCOVERY_PERIOD_MS    702

// ================================ Level1 =====================================
struct rPktIDState_t {
    uint8_t rID;
    uint8_t State;
} __attribute__ ((__packed__));

struct rPktHeader_t : public rPktIDState_t {
    uint8_t Length;
} __attribute__ ((__packed__));

template <uint32_t Sz>
struct rPktWithData_t {
    uint8_t rID;
    uint8_t Length;
    uint8_t Data[Sz];
} __attribute__ ((__packed__));

// Buffers
#ifdef DEVICE

#endif
#ifdef GATE
#define RRX_PKT_CNT     100     // Count of received pkts
#define RRX_PKT_DATA_SZ RDATA_CNT
#define RRX_BUF_SZ      ((sizeof(rPktHeader_t) + RRX_PKT_DATA_SZ) * RRX_PKT_CNT)

#define RTX_PKT_CNT     100     // Size of buffer of pkts to transmit
#define RTX_PKT_DATA_SZ 180     // Size of data in a single data pkt
//#define RTX_BUF_SZ      ((1 + 1 + RTX_PKT_DATA_SZ) * RTX_PKT_CNT)
#define RTX_BUF_SZ      36
#endif

class rLevel1_t {
private:
    uint8_t SelfID;
    EventSource IEvtSrcRadioRx, IEvtSrcRadioTxEnd;
    // ==== Rx ====
    rPkt_t PktRx;
    BufChunkPut_t<rPktHeader_t, RRX_BUF_SZ> IRxBuf;
    inline uint8_t HandleRxDataPkt();
    // ==== Tx ====
    rPkt_t PktTx;       // Local rPkt to transmit
    rPktHeader_t IHdr;
    CircBufNumber_t<uint8_t, RTX_BUF_SZ> ITxBuf;  // Buffer containing pkts to transmit

    inline void PrepareDataPkt();
#ifdef DEVICE
    uint8_t RxRetryCounter; // to check if we get lost
    uint16_t GateN;   // Number of concentrator to use. Note, Number != ID.
    inline void IInSync();
    inline void IDiscovery();
    uint32_t ICalcWaitRx_ms(uint8_t RcvdSlot);
    void ISleepIfLongToWait(uint8_t RcvdSlot);
    inline void PrepareAck();
#endif
#ifdef GATE
    uint8_t SlotN;
    inline void PreparePingPkt();
    inline bool InsideCorrectSlot() { return (SlotN == ID2SLOT(IHdr.rID)); }
    CircBuf_t<rPktIDState_t, RTX_PKT_CNT> ITransmitted;
    inline void ICompleteTx(uint8_t AState);
#endif
public:
    void Init(uint16_t ASelfID);
#ifdef GATE
    void SetID(uint16_t ASelfID);
#endif
    // Rx
    uint8_t GetReceivedPkt(rPktWithData_t<RRX_PKT_DATA_SZ> *PPkt) { return IRxBuf.GetWholePkt((uint8_t*)PPkt); }
    void RegisterEvtRx(EventListener *PEvtLstnr, uint8_t EvtMask) { chEvtRegisterMask(&IEvtSrcRadioRx, PEvtLstnr, EvtMask); }
    // Tx
    uint8_t AddPktToTx(uint8_t rID, uint8_t *Ptr, uint32_t Length);
    uint8_t GetTransmittedState(rPktIDState_t *PState) { return ITransmitted.Get(PState); }
    void RegisterEvtTx(EventListener *PEvtLstnr, uint8_t EvtMask) { chEvtRegisterMask(&IEvtSrcRadioTxEnd, PEvtLstnr, EvtMask); }
    // Inner use
    inline void Task();
};

extern rLevel1_t rLevel1;

#endif /* LVL1_ASSYM_H_ */
