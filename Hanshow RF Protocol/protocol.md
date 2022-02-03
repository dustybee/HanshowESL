# Hanshow RF Protocol

---

### Radio specifications

| Radio               |                  |
| ------------------- | ---------------- |
| Operating Frequency | 201MHz - 2480MHz |
| Number of channels  | 157              |
| Modulation type     | GFSK             |
| Channel Seperation  | 0.5MHz (500KHz)  |
| Uplink              | 500Kbps          |
| Downlink            | 100Kbps          |

---

### Heartbeat

There are two types of heartbeat messages which i was able to receive on 2.401GHz: **NORMAL_HEARTBEAT** and **TABLE_HEARTBEAT**

The  heartbeat is identified by the Heartbeat Control number (CTRL). 0x81 for the normal Heartbeat, 0x84 for the table Heartbeat. 

The normal heartbeat is sent roughly every 3 minutes. I have not found out when the table heartbeat gets sent.

The example signals could be wrong at the end. I cannot quite figure out where the CRC starts and ends.

##### Normal Heartbeat

I could not accurately get past the ESL Info section because i didn't understand the ESL_INFO struct.

| Preamble | Sync Word | CTRL | Wakeup ID | ESL ID   | Wakeup Channel | Group wakeup channel | Data Channel | Netmask | ESL Info | Display ID | Display Temperature | ROM Version | Page Map | Page CRC Map | Default CRC Page | CRC  |
| -------- | --------- | ---- | --------- | -------- | -------------- | -------------------- | ------------ | ------- | -------- | ---------- | ------------------- | ----------- | -------- | ------------ | ---------------- | ---- |
| AAAAAAAA | 52567853  | 81   | 508103    | 50c3cc62 | 97             | 97                   | 97           | 1d      | 23       | 2026a354   | 04                  | 0c          | 25       | fc           | 3400             | 00cb |

##### Table Heartbeat

| Preamble | Sync Word | CTRL | Product ID | Display Height | Display Width | Display DPI | Max Page | Flash Size | Max Package | Display Delay Time | OSD Process Time | Display Size | Reserve Buffer | CRC  |
| -------- | --------- | ---- | ---------- | -------------- | ------------- | ----------- | -------- | ---------- | ----------- | ------------------ | ---------------- | ------------ | -------------- | ---- |
| AAAAAAAA | 52567853  | 84   | 2026a354   | 7a00           | fa00          | 83          | 04       | e800       | cc00        | 14                 | 01               | d500         | 0020030000     | e21f |

---

Universal Radio Hacker settings to receive the heartbeat messages.

| Record Signal |        |
| ------------- | ------ |
| Device        | HackRF |
| Frequency     | 2,401G |
| Sample rate   | 2,0M   |
| Bandwidth     | 2.0M   |
| Gain          | 0      |
| IF Gain       | 8      |
| Baseband Gain | 12     |
| DC Correction | On     |


| Interpretation  |              |
| --------------- | ------------ |
| Noise           | 0,0000       |
| Center          | 0,0000       |
| Samples/Symbol  | 20           |
| Error tolerance | 0            |
| Modulation      | FSK          |
| bits/Symbol     | 1            |
| Encoding        | NRZ + Invert |

---

###### Heartbeat CTRL definition

```c
#define HEARTBEAT_LEN                    26
#define CTRL_HBR_NORMAL                 (0x81)
#define CTRL_HBR_REED                   (0x82)
#define CTRL_HBR_REQ                    (0x83)

#define CTRL_TABLE_HBR                  (0x84)
```

###### ESL_INFO struct 

```c
typedef struct
{
    UINT8 battery:3;
    UINT8 reserve1:2;
    UINT8 encryption_enable:1;
    UINT8 isencryption:1;
    UINT8 flash_err:1;
}HARTESL_INFO_T;
```

###### Table heartbeat struct

```c
struct esl_table_regist{
    UINT8 ctrl;
    UINT32 product_id;
    UINT16 screen_high;
    UINT16 screen_width;
    UINT8  screen_dpi;
    UINT8  max_page;
    UINT16 flash_size;
    UINT16 max_package;
    UINT8  screen_delay_time;
    UINT8  osd_process_time;
    UINT16  screen_size;
    UINT8  reserve_buf[5];
    UINT16 crc;
}esl_table_regist_buf;
```

###### Normal heartbeat struct

```c
struct esl_regist {
    UINT8 ctrl;
    UINT8 set_wkup_id[3];
    RFID eslid;
    UINT8 set_wkup_chn;
    UINT8 grp_wkup_chn;
    UINT8 data_chn;
    UINT8 esl_netmask;
    HARTESL_INFO_T info;
    UINT32 screen_id;
    UINT8 ser_wor_time;
    UINT8 temperture;
    UINT8 rom_version;
    UINT8 page_map;
    UINT8 page_crc_map;
    UINT16 default_page_crc; 
    UINT16 crc;
}esl_regist_buf;
```

---