#include "MARKET_DATA_ENDPOINTS.H"
#include "Request.h"

String ping() {
  String BASE = "/api/v3/ping";
  String LINK = BASE;
  return GET_Request(LINK); }

String serverTime() {
  String BASE = "/api/v3/time";
  String LINK = BASE;
  return GET_Request(LINK); }

String exchangeInfo(String pair) {
  String BASE = "/api/v3/exchangeInfo";
  String PARAMS = String("?") + String("symbol=") + pair;
  String LINK = BASE + PARAMS;
  return GET_Request(LINK); }

String depth(String pair, int limit) {
  if (limit != 5 && limit != 10 && limit != 20 && limit != 50 && 
      limit !=  100 && limit != 500 && limit != 1000 && limit !=  5000) {
        Serial.println("Limit not accepted for depth request");
    } else { 
      String BASE = "/api/v3/depth";
      String PARAMS = String("?") + String("symbol=") + pair + String("&") + 
                                    String("limit=") + limit;
      String LINK = BASE + PARAMS;
      return GET_Request(LINK); }  }

String trades(String pair, int limit) {
    String BASE = "/api/v3/trades";
    String PARAMS = String("?") + String("symbol=") + pair + String("&") + 
                                  String("limit=") + limit;
    String LINK = BASE + PARAMS;
    return GET_Request(LINK); }

String historicalTrades(String pair, int limit) {
    String BASE = "/api/v3/historicalTrades";
    String PARAMS = String("?") + String("symbol=") + pair + String("&") + 
                                  String("limit=") + limit;
    String LINK = BASE + PARAMS;
    return GET_Request(LINK); }

String aggTrades(String pair, int limit) {
    String BASE = "/api/v3/aggTrades";
    String PARAMS = String("?") + String("symbol=") + pair + String("&") + 
                                  String("limit=") + limit;
    String LINK = BASE + PARAMS;
    return GET_Request(LINK); }

String getKlines(String pair, String interval, int limit) {
  String BASE = "/api/v3/klines";
  String PARAMS = String("?") + String("symbol=") + pair + String("&") + 
                                String("interval=") + interval + String("&") + 
                                String("limit=") + limit;
  String LINK = BASE + PARAMS;
  return GET_Request(LINK); }

String avgPrice(String pair) {
  String BASE = "/api/v3/avgPrice";
  String PARAMS = String("?") + String("symbol=") + pair;
  String LINK = BASE + PARAMS;
  return GET_Request(LINK); }

String TPC_Statistics_24hr(String pair) {
  String BASE = "/api/v3/ticker/24hr";
  String PARAMS = String("?") + String("symbol=") + pair;
  String LINK = BASE + PARAMS;
  return GET_Request(LINK); }

String Symbol_Price_Ticker(String pair) {
  String BASE = "/api/v3/ticker/price";
  String PARAMS = String("?") + String("symbol=") + pair;
  String LINK = BASE + PARAMS;
  return GET_Request(LINK); }

String Symbol_Order_Book_Ticker(String pair) {
  String BASE = "/api/v3/ticker/bookTicker";
  String PARAMS = String("?") + String("symbol=") + pair;
  String LINK = BASE + PARAMS;
  return GET_Request(LINK); }
