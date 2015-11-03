md order

copy /y nrfburn-B_Cu.gbl        order\nrfburn.GBL
copy /y nrfburn-B_Mask.gbs      order\nrfburn.GBS
copy /y nrfburn-B_SilkS.gbo     order\nrfburn.GBO
copy /y nrfburn-Edge_Cuts.gbr   order\nrfburn.GKO
copy /y nrfburn-F_Cu.gtl        order\nrfburn.GTL
copy /y nrfburn-F_Mask.gts      order\nrfburn.GTS
copy /y nrfburn-F_SilkS.gto     order\nrfburn.GTO
copy /y nrfburn.drl             order\nrfburn.TXT

cd order

7za a -tzip nrfburn *.*
