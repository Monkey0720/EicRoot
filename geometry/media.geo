
// -------------------------------------------------------------------------------------
//
// Standard basic elements (the ones which are shared between different detectors, 
// have known properties and by no means should be touched/tuned);
//
vacuum             1   1.e-16  1.e-16 1.e-16
                   0  1  30.  .001
                   0       
Galactic           1   1.e-16  1.e-16 1.e-16
                   0  1  30.  .001
                   0       
//vacuum             3  14.01  16.000  39.95    7.  8.  18.  1.205e-3  0.755  0.231  0.014
//                   0  1  30.  .001
//                   0

hydrogen           1  1.001  1.0  .07
		   0  0  0  .0001 
		   0

helium             1   4.00    2.0    0.164e-3
                   0  0  20.  .001
                   0
// Should be correct?
liquid-helium      1   4.00    2.0    0.125
                   0  0  20.  .001
                   0

beryllium          1   9.01    4.0    1.848
                   0  0  20.  .001
                   0

aluminum           1  26.98   13.0    2.70
                   0  1  20.  .001
                   0
aluminium          1  26.98   13.0    2.70
                   0  1  20.  .001
                   0

//
// -> THINK WHY TUTORIAL TRACKING DOES NOT LIKE SMALL EPSIL SETTING
//    IN THIS FILE (JUST STOPS WITH TOO MANY STEPS UNDER CERTAIN 
//    CIRCUMSTANCES);
//
// NB: 'epsil' is given in [mm] in this file?;
//
silicon            1  28.086  14.0    2.33
                   1  1  20.  .001
                   0         
                                            
iron               1  55.847  26.0    7.87
                   1  1  70.  .001
                   0                       
StainlessSteel     1  55.847  26.0    7.87
                   1  1  70.  .001
                   0                       
STAINLESS-STEEL    1  55.847  26.0    7.87
                   1  1  70.  .001
                   0                      
// All fake for JLEIC;
GLASS_LEAD         1  55.847  26.0    7.87
                   1  1  70.  .001
                   0   
Kryptonite         1  55.847  26.0    7.87
                   1  1  70.  .001
                   0  
Al                 1  55.847  26.0    7.87
                   1  1  70.  .001
                   0  
Be                 1  55.847  26.0    7.87
                   1  1  70.  .001
                   0 
Cu                 1  55.847  26.0    7.87
                   1  1  70.  .001
                   0  
Si                 1  55.847  26.0    7.87
                   1  1  70.  .001
                   0  
det1_beamline_pipe_BeAl                 1  55.847  26.0    7.87
                   1  1  70.  .001
                   0  
MAT_det1_rich_dual_ionside_gas                 1  55.847  26.0    7.87
                   1  1  70.  .001
                   0    
MAT_det1_rich_dual_ionside_aerogel                 1  55.847  26.0    7.87
                   1  1  70.  .001
                   0     
acrylic_a          1  55.847  26.0    7.87
                   1  1  70.  .001
                   0    
Air_Opt            1  55.847  26.0    7.87
                   1  1  70.  .001
                   0           
                                
copper             1  63.54   29.0    8.96
                   0  0  20.  .001
                   0
 
tungsten           1 183.84   74.0   19.25
                   0  1  20.  .00001
                   0

lead               1 207.2    82.0   11.34
                   1  1  20.  .001
                   0

diamond            1 12.01    6.0    3.5
                   1  1  20.   0.001
                   0

// Carbon with a density tuned to fit exactly X0=10cm; helpful to build fake material 
// layers of a given rad. length (say, need just 1mm thick layer to match 1% rad.length);
X0=10cm            1  12.011   6.0    4.24975
                   0  1  20.  .001
                   0      
//
// -------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------
//
// Standard basic mixtures; same idea as for standard elements: don't touch!;
//
//air                3  14.01  16.000  39.95    7.  8.  18.  1.205e-3  0.755  0.231  0.014
//                   0  1  70.  .001
//                   0

// Well, H2O :-);
water             -2   1.008 16.000           1.  8.       1.00         2  1
                   0  1  20.  .001                                                                                                             
                   0  

// Follow PDG entry: C6-H5-CH=CH2 (C8-H8 total, so 1:1);
polystyrene	  -2  12.01   1.008	      6.  1.       1.032	1  1	
		   1  1	 20.  .00001	
                   0    

// Assume SiO2 and density as in the PDG book;
quartz            -2  28.055 16.000          14.  8.       2.200        1  2
                   0  1  20.  .001
                   0

// Argon CO2 (70/30)                                                                                                                        
arco27030         -3  39.948 12.01   16.000  18.  6.   8.  0.0019      700    100    200   
                   1  1  20.  .001                                                                                                             
                   0    
//
// -------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------
//
// MAPS-specific materials; even if there are duplicates, keep them decoupled
// from other detectors;
//
// Assume it is pure C^12; tune density to get X0~26.1cm (ALICE ITS TDR, p.55);
MapsCarbonFiber    1  12.011                         6.0              1.63
                   0  1  20.  .001
                   0

// Use C22H10N2O5 composition (PDG) and tune density to get X0~28.4cm (ALICE ITS TDR, p.55);
MapsKapton        -4  14.006  12.011  1.008  16.000  7.0 6.0 1.0 8.0  1.42   2 22 10 5
                   0  0  20.  .001
                   0
//
// -------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------
//
// GEM-specific materials; 
//

// Use C22H10N2O5 composition (PDG) and tune density to get FIXME: X0~28.6cm;
GemKapton         -4  14.006  12.011  1.008  16.000  7.0 6.0 1.0  8.0  1.42   2 22 10 5
                   0  0  20.  .001
                   0

// Carelessly copy over from PANDA media.geo; FIXME: tune density;
GemG10             4  12.010   1.008 16.000  28.086  6.0 1.0 8.0 14.0  1.70 0.259 0.288 0.248 0.205
                   0  1  20.  .001
                   0

// FIXME: Nomex honeycomb from PANDA; radlen 1430cm (may be a bit different from STAR);
GemNomex	  -4   1.008  12.011 16.000  14.007  1.0 6.0 8.0  7.0  0.056  18. 14. 2. 2.
		   0  1  30.  .001
		   0
//
// -------------------------------------------------------------------------------------
                                                              
// -------------------------------------------------------------------------------------
//
// MuMegas-specific materials; 
//

// Basically copy over GEM GemKapton material as of 2015/02/02;
MuMegasKapton     -4  14.006  12.011  1.008  16.000  7.0 6.0 1.0  8.0  1.42   2 22 10 5
                   0  0  20.  .001
                   0

// Carelessly copy over from PANDA media.geo; FIXME: replace by FR4 eventually;
MuMegasG10         4  12.010   1.008 16.000  28.086  6.0 1.0 8.0 14.0  1.70 0.259 0.288 0.248 0.205
                   0  1  20.  .001
                   0

// Basically copy over from GEM section as of 2015/02/04;
MuMegasCarbonFiber 1  12.011                         6.0              1.63
                   0  1  20.  .001
                   0
//
// -------------------------------------------------------------------------------------                                                   

// -------------------------------------------------------------------------------------
//
// T1018-specific materials; 
//

// Assume high brass, so 65% Cu & 35% Zi by weight; density ~8.4g/cm^3;
brass              2  63.54  65.39  29.  30.  8.4  0.65  0.35
                   0  0  20.  .001
                   0

// Kuraray values (and yes, they give proportion by atoms);
PMMA 		  -3  12.01   1.008   16.000     6.  1.  8.    1.190     3.6  5.7  1.4
		   1  1	 20.  .00001	
                   0    

//
// W:Sn:Epoxy mixtures; see W-Sn-Epoxy.c for calculation details;
//

// Pure epoxy; assume C18-H20-O3 with density 1.150g/cm^3;
Epoxy-00          -3                 12.011 1.008 16.000             6.0 1.0 8.0   1.150                     18     20      3
                   0  1  20.  .001
                   0

// Original T1018 mixture W:Epoxy (no Sn) 0.9656 : 0.0344 by weight; roughly ~12.18 g/cm^3 density;
W-Epoxy-00         4 183.840         12.011 1.008 16.000   74.0      6.0 1.0 8.0  12.179   0.9656        0.0262 0.0024 0.0058  
                   0  1  20.  .001
                   0

// Whatever comes out with square fibers in may'2016: 3090g W & 240g epoxy -> mixture W:Epoxy (no Sn) 0.9279 : 0.0721 by weight; 
// roughly ~8.86 g/cm^3 density;
W-Epoxy-01         4 183.840         12.011 1.008 16.000   74.0      6.0 1.0 8.0   8.861   0.9279        0.0548 0.0051 0.0122
		   0  1  20.  .001
		   0

// Mixture W:Sn:Epoxy 0.4745 : 0.4745 : 0.0510 by weight; 
W-Sn-Epoxy-00      5 183.840 118.710 12.011 1.008 16.000   74.0 50.0 6.0 1.0 8.0   7.412   0.4745 0.4745 0.0388 0.0036 0.0086
                   0  1  20.  .001
                   0

// Mixture W:Sn:Epoxy 0.5745 : 0.3788 : 0.0467 by weight; 01..05 versions assume epoxy volume fraction at ~32.87% (same as
// in W-Sn-Epoxy-00); so these mixtures may differ in production;
W-Sn-Epoxy-01      5 183.840 118.710 12.011 1.008 16.000   74.0 50.0 6.0 1.0 8.0   8.098   0.5745 0.3788 0.0355 0.0033 0.0079
                   0  1  20.  .001
                   0

// Mixture W:Sn:Epoxy 0.6745 : 0.2832 : 0.0423 by weight;     
W-Sn-Epoxy-02      5 183.840 118.710 12.011 1.008 16.000   74.0 50.0 6.0 1.0 8.0   8.930   0.6745 0.2832 0.0322 0.0030 0.0071
                   0  1  20.  .001
                   0

// Mixture W:Sn:Epoxy 0.7745 : 0.1875 : 0.0380 by weight; 
W-Sn-Epoxy-03      5 183.840 118.710 12.011 1.008 16.000   74.0 50.0 6.0 1.0 8.0   9.944   0.7745 0.1875 0.0289 0.0027 0.0064
                   0  1  20.  .001
                   0

// Mixture W:Sn:Epoxy 0.8745 : 0.0918 : 0.0337 by weight; 
W-Sn-Epoxy-04      5 183.840 118.710 12.011 1.008 16.000   74.0 50.0 6.0 1.0 8.0  11.219   0.8745 0.0918 0.0256 0.0024 0.0057
                   0  1  20.  .001
                   0

// Mixture W:Sn:Epoxy 0.9705 : 0.0000 : 0.0295 by weight; just cook pure-W-powder absorber the same way as 00..04, 
// keeping epoxy volume fraction at ~32.87% (so there is a difference compared to W-Epoxy-00);  
W-Sn-Epoxy-05      5 183.840 118.710 12.011 1.008 16.000   74.0 50.0 6.0 1.0 8.0  12.802   0.9705 0.0000 0.0224 0.0021 0.0050
                   0  1  20.  .001
                   0

// Mixture W:Sn:Epoxy 0.7095 : 0.2365 : 0.0540 by weight; real-life composition for May'2015 test run (density as measured);
W-Sn-Epoxy-06      5 183.840 118.710 12.011 1.008 16.000   74.0 50.0 6.0 1.0 8.0   8.646   0.7095 0.2365 0.0411 0.0038 0.0091
                   0  1  20.  .001
                   0
//
// -------------------------------------------------------------------------------------
                                 
// -------------------------------------------------------------------------------------
//
Air                3  14.01  16.000  39.95    7.  8.  18.  1.205e-3  0.755  0.231  0.014
                   0  1  30.  .001
                   0
//
// -------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------
//

// Assume Al & Cu only at 0.94 : 0.06 by weight; add other components later if needed; 
AA2219             2  26.98  63.55     13.  29.   2.84  0.940  0.060  
                   0  1  30.  .001
                   0
//
// -------------------------------------------------------------------------------------



//
// FIXME: the rest of this file requies a clean-up;
//

// Think twice before changing density here!;
carbon             1  12.011  6.0  2.265
                   0  1  20.  .001
                   0      
// Well, assume it is almost pure C^12 with 1.76g/cm^3 density;
CarbonFiber        1  12.011  6.0  1.76
                   0  1  20.  .001
                   0
// Voluntary consider to use effective density of 1/5 for carbon fiber 
// construction elements in order to effectively fill more bulky volumes;
// NEVER change this without modifying geometry creation C files!; may be 
// not a good idea alltogether;
CarbonFiberAssy    1  12.011  6.0  0.352
                   0  1  20.  .001
                   0



// Used for PANDA FTOF import (debugging);
polyvinyltoluene  -2	12.01	1.008	6.	1.	1.032	9.	10.	
		   1  1	 20.  .001	
                   0
                        

// Check kapton parameters vs. STAR design (why they differ?); 
kapton             -4  14.006  12.011  1.008  16. 7. 6. 1. 8. 1.42 2 22 10 5
                   0  0  20.  .001
                   0

pwo               -3  207.19  15.99  183.85  82.  8.  74.  8.28  1.  4.  1.
		   1  1  30.  .001 
                   0         

// Assume composition "(CH3)2 Si O2", so C2H6SiO2 total; whether it 
// is correct or not; and some default density say 1g/cm^3;
SiliconeResinD    -4    12.011 1.008 28.0855 15.9994    6. 1. 14.  8.  1.00   2. 6. 1. 2.  
		   1  1  30.  .001 
                   0         

// PDG: "CH2=C(CH3)CO2 CH3", so C5H8O2; take 1.20g/cm^3 density;
lucite            -3    12.011 1.008 15.9994    6. 1. 8.   1.20    5. 8. 2.  
		   1  1  30.  .001 
                   0         


// !!! Check this entry later; effective tungsten/epoxy/fiber mixture; 
WEpoxySciMix       3  12.011 1.008 183.85  6.  1.  74.  10.17  0.041 0.009 0.950
		   1  1  30.  .001 
                   0     
// Check this entry later; effective tungsten/epoxy mixture; should of course
// differ from WEpoxySciMix;
//WEpoxyMix          3  12.011 1.008 183.85  6.  1.  74.  12.46  0.025 0.006 0.969
//		   1  1  30.  .001 
//                 0     
//WEpoxyMix          3  12.011 1.008 183.85  6.  1.  74.  13.60  0.020 0.002 0.978
//		   1  1  30.  .00001 
//                 0    
WEpoxyMix          3  12.011 1.008 183.85  6.  1.  74.  12.18  0.029 0.002 0.969
		   1  1  30.  .00001 
                   0     
// Identical to polystyrene for now; fix density later;
EpoxySciMix	  -2  12.01	1.008	6.	1.	1.05	1. 1.	
		   1  1	 20.  .001	
                   0    
// Identical to polystyrene for now; fix density later;
Epoxy 	     	  -2  12.01	1.008	6.	1.	1.05	1. 1.	
		   1  1	 20.  .001	
                   0    
    
// Carelessly copy over from PANDA media.geo;
G10                4  12.01 1.008 16. 28.09 6.  1.  8.  14. 1.7 0.259 0.288 0.248 0.205
                   0  1  20.  .001
                   0

// (More or less) matches in composition and average density to the T1018 test run HCAL design;
PbSciMix           4    207.2 55.847 12.011 1.008    82. 26. 6.  1.   8.48    0.946 0.029 0.004  0.021
		   1  1  30.  .001 
                   0     



//nomex honeycomb from PANDA; radlen 1430cm (may be a bit different from STAR);
honeycomb	    -4 1.0079 12.011 15.999 14.0067 1. 6. 8. 7. 0.056 18. 14. 2. 2.
		    0 1 30. .5
		    0

// Si:O:H=1:6:8 for aerogel in RICH, density 0.1 g/cm3, everything like in HERMES
AeroFake	3 28.086 15.9994 1.00797 14. 8. 1.  0.1 0.21 0.73 0.06    
 	        0  	1  	20.  	.001	   	   	   	 
  	        2
		1.77    50000      1.0      1.03
		11.81   50000      1.0      1.03


RICHgas_CO2_dis   -2  12. 16. 6. 8.  1.977e-3  1 2
                 0  1  20.  .001
                65
		1.77    50000      1.0      1.000446242
		2.0    50000      1.0      1.000447917
		2.1    50000      1.0      1.000448714
		2.2    50000      1.0      1.000449552
		2.3    50000      1.0      1.000450433
		2.4    50000      1.0      1.000451357
		2.5    50000      1.0      1.000452324
		2.6    50000      1.0      1.000453335
		2.7    50000      1.0      1.00045439
		2.8    50000      1.0      1.00045549
		2.9    50000      1.0      1.000456636
		3.0    50000      1.0      1.000457829
		3.1    50000      1.0      1.000459068
		3.2    50000      1.0      1.000460355
		3.3    50000      1.0      1.00046169
		3.4    50000      1.0      1.000463075
		3.5    50000      1.0      1.00046451
		3.6    50000      1.0      1.000465996
		3.7    50000      1.0      1.000467533
		3.8    50000      1.0      1.000469123
		3.9    50000      1.0      1.000470767
		4.0    50000      1.0      1.000472465
		4.1    50000      1.0      1.00047422
		4.2    50000      1.0      1.000476031
		4.3    50000      1.0      1.0004779
		4.4    50000      1.0      1.000479829
		4.5    50000      1.0      1.000481818
		4.6    50000      1.0      1.000483869
		4.7    50000      1.0      1.000485983
		4.8    50000      1.0      1.000488161
		4.9    50000      1.0      1.000490406
		5.0    50000      1.0      1.000492718
		5.1    50000      1.0      1.0004951
		5.2    50000      1.0      1.000497553
		5.3    50000      1.0      1.000500078
		5.4    50000      1.0      1.000502678
		5.5    50000      1.0      1.000505355
		5.6    50000      1.0      1.00050811
		5.7    50000      1.0      1.000510946
		5.8    50000      1.0      1.000513865
		5.9    50000      1.0      1.000516869
		6.0    50000      1.0      1.00051996
		6.1    50000      1.0      1.000523142
		6.2    50000      1.0      1.000526416
		6.3    50000      1.0      1.000529786
		6.4    50000      1.0      1.000533255
		6.5    50000      1.0      1.000536824
		6.6    50000      1.0      1.000540499
		6.7    166.7      1.0      1.000544281
		6.89    33.3      1.0      1.000551777
		7.09    20.0      1.0      1.00056013
		7.29    1.67      1.0      1.000568991
		7.51    0.5       1.0      1.000579367
		7.75    0.2       1.0      1.000591499
		8.0     0.1       1.0      1.000605123
		8.27    0.0667    1.0      1.000621082
		8.55    0.0667    1.0      1.000639155
		8.86    0.05      1.0      1.000661203
		9.18    0.05      1.0      1.000686535
		9.64    0.05      1.0      1.000728383
		9.92    0.143      1.0      1.000757597
		10.33    1.0       1.0      1.000806643
		10.78    0.01      1.0      1.000871174
		11.27    0.002      1.0      1.000958375
		11.81    0.0033      1.0      1.00108348

RICHgas_CO2_dis+   -2  12. 16. 6. 8.  1.977e-3  1 2
                 1  1  20.  .001
                65
		1.77    50000      1.0      1.000446242
		2.0    50000      1.0      1.000447917
		2.1    50000      1.0      1.000448714
		2.2    50000      1.0      1.000449552
		2.3    50000      1.0      1.000450433
		2.4    50000      1.0      1.000451357
		2.5    50000      1.0      1.000452324
		2.6    50000      1.0      1.000453335
		2.7    50000      1.0      1.00045439
		2.8    50000      1.0      1.00045549
		2.9    50000      1.0      1.000456636
		3.0    50000      1.0      1.000457829
		3.1    50000      1.0      1.000459068
		3.2    50000      1.0      1.000460355
		3.3    50000      1.0      1.00046169
		3.4    50000      1.0      1.000463075
		3.5    50000      1.0      1.00046451
		3.6    50000      1.0      1.000465996
		3.7    50000      1.0      1.000467533
		3.8    50000      1.0      1.000469123
		3.9    50000      1.0      1.000470767
		4.0    50000      1.0      1.000472465
		4.1    50000      1.0      1.00047422
		4.2    50000      1.0      1.000476031
		4.3    50000      1.0      1.0004779
		4.4    50000      1.0      1.000479829
		4.5    50000      1.0      1.000481818
		4.6    50000      1.0      1.000483869
		4.7    50000      1.0      1.000485983
		4.8    50000      1.0      1.000488161
		4.9    50000      1.0      1.000490406
		5.0    50000      1.0      1.000492718
		5.1    50000      1.0      1.0004951
		5.2    50000      1.0      1.000497553
		5.3    50000      1.0      1.000500078
		5.4    50000      1.0      1.000502678
		5.5    50000      1.0      1.000505355
		5.6    50000      1.0      1.00050811
		5.7    50000      1.0      1.000510946
		5.8    50000      1.0      1.000513865
		5.9    50000      1.0      1.000516869
		6.0    50000      1.0      1.00051996
		6.1    50000      1.0      1.000523142
		6.2    50000      1.0      1.000526416
		6.3    50000      1.0      1.000529786
		6.4    50000      1.0      1.000533255
		6.5    50000      1.0      1.000536824
		6.6    50000      1.0      1.000540499
		6.7    166.7      1.0      1.000544281
		6.89    33.3      1.0      1.000551777
		7.09    20.0      1.0      1.00056013
		7.29    1.67      1.0      1.000568991
		7.51    0.5       1.0      1.000579367
		7.75    0.2       1.0      1.000591499
		8.0     0.1       1.0      1.000605123
		8.27    0.0667    1.0      1.000621082
		8.55    0.0667    1.0      1.000639155
		8.86    0.05      1.0      1.000661203
		9.18    0.05      1.0      1.000686535
		9.64    0.05      1.0      1.000728383
		9.92    0.143      1.0      1.000757597
		10.33    1.0       1.0      1.000806643
		10.78    0.01      1.0      1.000871174
		11.27    0.002      1.0      1.000958375
		11.81    0.0033      1.0      1.00108348

RICHglass          -2  28.09  16.  14.  8.  2.2  1.  2.
                   1  0  20.  .0001
                   61
                   6.1997     0.22529        1.0        0
                   5.9045     0.1862         1.0        0
                   5.6361     0.15901        1.0        0
                   5.391      0.14713        1.0        0
                   5.1664     0.13963        1.0        0
                   4.9598     0.13898        1.0        0
                   4.769      0.13762        1.0        0
                   4.5924     0.13622        1.0        0
                   4.4284     0.13868        1.0        0
                   4.2757     0.13951        1.0        0
                   4.1331     0.14031        1.0        0
                   3.9998     0.14073        1.0        0
                   3.8748     0.1409         1.0        0
                   3.7574     0.13977        1.0        0
                   3.6469     0.14205        1.0        0
                   3.5427     0.14072        1.0        0
                   3.4443     0.1396         1.0        0
                   3.3512     0.13826        1.0        0
                   3.263     0.13665         1.0        0
                   3.1793     0.13513        1.0        0
                   3.0998     0.13463        1.0        0
                   3.0242     0.13287        1.0        0
                   2.9522     0.13182        1.0        0
                   2.8836     0.13084        1.0        0
                   2.818      0.12824        1.0        0
                   2.7554     0.12601        1.0        0
                   2.6955     0.12622        1.0        0
                   2.6382     0.12681        1.0        0
                   2.5832     0.12193        1.0        0
                   2.5305     0.12011        1.0        0
                   2.4799     0.12109        1.0        0
                   2.4313     0.11908        1.0        0
                   2.3845     0.11526        1.0        0
                   2.3395     0.11364        1.0        0
                   2.2962     0.11385        1.0        0
                   2.2544     0.12015        1.0        0
                   2.2142     0.11935        1.0        0
                   2.1753     0.11712        1.0        0
                   2.1378     0.1208         1.0        0
                   2.1016     0.12021        1.0        0
                   2.0666     0.11909        1.0        0
                   2.0327     0.11783        1.0        0
                   1.9999     0.12257        1.0        0
                   1.9682     0.1215         1.0        0
                   1.9374     0.12199        1.0        0
                   1.9076     0.12494        1.0        0
                   1.8787     0.13101        1.0        0
                   1.8507     0.12089        1.0        0
                   1.8234     0.12284        1.0        0
                   1.797      0.12569        1.0        0
                   1.7713     0.13136        1.0        0
                   1.7464     0.13307        1.0        0
                   1.7221     0.13705        1.0        0
                   1.6985     0.13844        1.0        0
                   1.6756     0.13753        1.0        0
                   1.6533     0.14416        1.0        0
                   1.6315     0.14761        1.0        0
                   1.6103     0.14953        1.0        0
                   1.5897     0.15218        1.0        0
                   1.5695     0.15315        1.0        0
                   1.5499     0.15719        1.0        0

CsI               -2  132.9054  126.9045 55.  53. 4.53  1  1 
                  1  1  20. .00001
             	  2
		  1.77       50000.            1.0        1.0003
		  10.5       50000.            1.0        1.0003


// -------------------------------------------------------------------------------------
//
// RD11-related materials; simlified versions for now; !!! ALL PARAMETERS CAN BE FAKE !!!;
//

// Si:O = 1:2 for RD11 silica aerogel; density 0.02 g/cm^3;
AerogelRD11    -2 28.086 15.9994  14. 8.    0.02    1.0  2.0    
 	        0  	1  	20.  	.001	   	   	   	 
  	        2
		2.034   100.00      1.0      1.024
		4.136   100.00      1.0      1.024

// C^5 : H^8 : O^2 for RD11 acrylic; density 1.19 g/cm^3;
AcrylicRD11    -3    12.011 1.008 15.9994    6. 1. 8.   1.19    5. 8. 2.  
		   1  1  30.  .001    	   	   	 
  	        2
		2.034   100.00      1.0      1.490
		4.136   100.00      1.0      1.490

CO2RD11        -2  12. 16. 6. 8.  1.977e-3  1 2	  
		   1  1  30.  .001    	   	   	   	 
  	        2
		2.034   1000.00      1.0      1.0005
		4.136   1000.00      1.0      1.0005

SensorRD11      1  28.086  14.0    2.33
                   1  1  20.  .0001 	   	   	   	 
  	        2
		2.034   0.0001      0.0      1.00001
		4.136   0.0001      0.0      1.00001
//
// -------------------------------------------------------------------------------------

// ----- Caution with putting materials below that line -----
// The next materials must specify additional parameters!

AUTONULL

//TPCmixture	3  20.1797 12.0107 15.9994  10. 6. 8.  0.0009222269   0.8049456004 0.0532325947 0.1418218049
//		1 1   20. 0.001 
//		99. 0.5 0.0001 0.00001 
//		0
                                                                     
// Argon CO2 (70/30);                  
//
// -> !!! think later, whether 1cm max step suffices to get momentum resolution;
//                                                                     
arco27030mmg      -3  39.948 12.01 15.9994 18. 6. 8. 0.0019 700 100 200                                                                    
                   1 1   20. 0.001                                                                                                          
                   20. 1. 0.0001 0.00001                                                                                                      
                   0                           
           
// Ar(95):CF4(3):iC4H10(2) by volume -> so the "molecule" will be Ar^3325/C^41/F^84/H^50;
//  assume Ar densityis 1.784g/L -> mixture density is 1.784*(0.95 + 0.03*88/40 + 0.02*58/40) ~1.864g/L;
//
// -> !!! think later, whether 1cm max step suffices to get momentum resolution;
//
ArCF4iC4H10       -4  39.948 12.011 18.998 1.008 18. 6. 9. 1. 1.864e-3 3325 41 84 50
                   1 1   20. 0.001                                                                                                          
                   20. 1. 0.0001 0.00001                                                                                                      
                   0    


// Si:0:H=1:6:8 for aerogel in RICH, density 0.1 g/cm3, everything like in HERMES
Aerogel		3 28.086 15.9994 1.00797 14. 8. 1.  0.1 0.21 0.73 0.06    
 	        0  	1  	3.  	.001                                                                                                      
                   20. 1. 0.0001 0.00001 	   	   	   	 
  	        0

// freon gas for RICH
C4F10  	-2  	12.01  	19.  	6.  	9.  	0.010625  	4.  	10.
  	0 	1 	3. 	.001                                                                                                     
                   20. 10. 0.0001 0.00001 	  	  	  	 
  	0

// Phenix RICH; assume 3.72kg/m^3 density;
CF4  	-2  	12.01  	19.  	6.  	9.  	0.00372  	1.  	4.
  	0 	1 	3. 	.001                                                                                                     
                   20. 10. 0.0001 0.00001 	  	  	  	 
  	0

air                3  14.01  16.000  39.95    7.  8.  18.  1.205e-3  0.755  0.231  0.014
                   0  1  70.  .001                                                                                                    
                   20. 10. 0.0001 0.00001
                   0
thin-air           3  14.01  16.000  39.95    7.  8.  18.  1.205e-8  0.755  0.231  0.014
                   0  1  70.  .001                                                                                                    
                   20. 10. 0.0001 0.00001
                   0
