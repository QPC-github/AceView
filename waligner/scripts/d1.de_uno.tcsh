#!bin/tcsh -ef

set run=$1

if ($USEMAGICBLAST == 1) then
  gunzip -c tmp/MAGICBLAST/$run/f2.*.introns.tsf.gz | bin/tsf -g $run --sumAll | gawk -F '\t' '{split($1,aa,"__");chrom=aa[1];split(aa[2],bb,"_");a2=bb[1];b1=bb[2];if(a2<b1){strand="Forward";a2--;a1=a2-12;b1++;b2=b1+10;ln=b1-a2-1;}else{strand="Reverse";a2++;a1=a2+10;b1--;b2=b1-10;ln=a2-b1-1;}nr=$4+$5;printf("INTRON\t%s\t%s\t%09d\t%09d\t%s\t%09d\t%09d\t%s\t%d\t%d\t%d\n",strand,chrom,a1,a2,chrom,b1,b2,feet,ln,nr,nperfect);}' | sort | gzip > tmp/OR/$run/d1.$run.de_uno.txt.gz
else
  gunzip -c tmp/PHITS_genome/$run/*.introns.gz  tmp/PHITS_mito/$run/*.introns.gz  | gzip > tmp/OR/$run/d1.$run.de_uno.txt.gz
endif
  ls -ls  tmp/OR/$run/d1.$run.de_uno.txt.gz
  touch tmp/OR/$run/d1.de_uno.done


echo done


