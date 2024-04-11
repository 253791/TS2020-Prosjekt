# Her er assembly koden til <esp_random> modulen.

```asm
40382ab8 <esp_random>:
40382ab8:	1141                	addi	sp,sp,-16
```
Reduserer stackpekeren (`sp`) med 16 for å allokere plass på stacken for lokal lagring.
```asm
40382aba:	c606                	sw	ra,12(sp)
```
Lagrer returadressen (`ra`) til funksjonen på stacken ved offset 12 bytes.
```asm
40382abc:	c422                	sw	s0,8(sp)
```
Lagrer register `s0` på stacken ved offset 8 bytes for å bevare verdien gjennom funksjonskallet.
```asm
40382abe:	a8afe0ef          	jal	ra,40380d48 <esp_clk_cpu_freq>
```
Hopper til funksjonen `esp_clk_cpu_freq` som returnerer CPU-frekvensen og lagrer returadressen i `ra`.
```asm
40382ac2:	842a                	mv	s0,a0
```
Flytter resultatet fra `esp_clk_cpu_freq` (lagret i `a0`) til `s0` for senere bruk.
```asm
40382ac4:	aa2fe0ef          	jal	ra,40380d66 <esp_clk_apb_freq>
```
Hopper til funksjonen `esp_clk_apb_freq` som returnerer APB-frekvensen, returadressen lagres i `ra`.
```asm
40382ac8:	02a44533          	div	a0,s0,a0
```
Dividerer CPU-frekvensen (`s0`) med APB-frekvensen (`a0`), og lagrer resultatet i `a0`.
```asm
40382acc:	4701                	li	a4,0
```
Setter `a4` til 0 som en initialverdi.
```asm
40382ace:	7e2026f3          	csrr	a3,0x7e2
```
Kopierer innholdet av kontroll- og statusregisteret `0x7e2` til `a3`.
```asm
40382ad2:	600267b7          	lui	a5,0x60026
```
Laster upper immediate `0x60026` inn i `a5`.
```asm
40382ad6:	0b078793          	addi	a5,a5,176 # 600260b0 <GPSPI2+0x20b0>
```
Legger til 176 til adressen i `a5`, peker nå til spesifikk maskinvareadresse `600260b0`.
```asm
40382ada:	439c                	lw	a5,0(a5)
```
Laster verdien på adressen `a5` inn i `a5`.
```asm
40382adc:	8f3d                	xor	a4,a4,a5
```
Utfører en XOR-operasjon mellom `a4` og `a5`, lagrer resultatet tilbake i `a4`.
```asm
40382ade:	3fc977b7          	lui	a5,0x3fc97
```
Laster en annen upper immediate `0x3fc97` inn i `a5`.
```asm
40382ae2:	94c7a783          	lw	a5,-1716(a5) # 3fc9694c <last_ccount.1>
```
Laster verdien fra en offset av `-1716` fra adressen i `a5`, peker til `3fc9694c`.
```asm
40382ae6:	40f687b3          	sub	a5,a3,a5
```
Subtraherer verdien i `a5` fra `a3`, lagrer resultatet i `a5`.
```asm
40382aea:	00451613          	slli	a2,a0,0x4
```
Shift left logisk av `a0` med 4 bits, lagrer resultatet i `a2`.
```asm
40382aee:	fec7e0e3          	bltu	a5,a2,40382ace <esp_random+0x16>
```
Hopper tilbake til adressen `40382ace` hvis `a5` er mindre enn `a2`.
```asm
40382af2:	3fc977b7          	lui	a5,0x3fc97
```
Laster `0x3fc97` til `a5` igjen.
```asm
40382af6:	94d7a623          	sw	a3,-1716(a5) # 3fc9694c <last_ccount.1>
```
Lagrer `a3` til adressen beregnet ved `-1716` offset fra `a5`.
```asm
40382afa:	600267b7          	lui	a5,0x60026
```
Laster `0x60026` til `a5` igjen.
```asm
40382afe:	0b07a503          	lw	a0,176(a5) # 600260b0 <GPSPI2+0x20b0>
```
Laster verdien fra adressen `600260b0` inn i `a0`.
```asm
40382b02:	8d39                	xor	a0,a0,a4
```
Utfører en XOR-operasjon mellom `a0` og `a4`, lagrer resultatet i `a0`.
```asm
40382b04:	40b2                	lw	ra,12(sp)
```
Laster `ra` fra stacken.
```asm
40382b06:	4422                	lw	s0,8(sp)
```
Laster `s0` fra stacken.
```asm
40382b08:	0141                	addi	sp,sp,16
```
Øker stackpekeren (`sp`) med 16 for å rydde opp i lokal lagring.
```asm
40382b0a:	8082                	ret
```
Returnerer fra funksjonen.

