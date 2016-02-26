md order

copy /y nrfburn-B.Cu.gbl        order\nrfburn.GBL
copy /y nrfburn-B.Mask.gbs      order\nrfburn.GBS
copy /y nrfburn-B.SilkS.gbo     order\nrfburn.GBO
copy /y nrfburn-Edge.Cuts.gm1   order\nrfburn.GKO
copy /y nrfburn-F.Cu.gtl        order\nrfburn.GTL
copy /y nrfburn-F.Mask.gts      order\nrfburn.GTS
copy /y nrfburn-F.SilkS.gto     order\nrfburn.GTO
copy /y nrfburn.drl             order\nrfburn.TXT

cd order

7za a -tzip nrfburn *.*
