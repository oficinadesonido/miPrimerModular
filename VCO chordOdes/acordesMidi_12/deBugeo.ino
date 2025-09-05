void deBugeo(){
  Serial.print("cvo ");
  Serial.print((cvO));
  Serial.print(" kCvo ");
  Serial.print((pCvo));
  Serial.print("  voct  ");
  Serial.print((Q16n16_to_float(voct)));
  Serial.print(" lee ");
  Serial.print((pPnota));
  Serial.print(" prom ");
  Serial.print((potO));
  Serial.print(" notar ");
  Serial.print(Q16n16_to_float(notar),4);
  Serial.println("  ");
}
