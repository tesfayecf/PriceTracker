#ifndef M_D_E //MARKET_DATA_ENDPOINTS
#define M_D_E

#ifdef ARDUINO_ARCH_MEGAAVR
#endif

#if (ARDUINO >=100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

String ping();

String serverTime();

String exchangeInfo(String pair);

String depth(String pair, int limit);

String trades(String pair, int limit);

String historicalTrades(String pair, int limit);

String aggTrades(String pair, int limit);

String getKlines(String pair, String interval, int limit);

String avgPrice(String pair);

String TPC_Statistics_24hr(String pair);

String Symbol_Price_Ticker(String pair);

String Symbol_Order_Book_Ticker(String pair);

#endif
