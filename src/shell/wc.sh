#count lines
wc -l < ./nowcoder.txt
cat ./nowcoder.txt | wc -l
wc -l ./nowcoder.txt | awk '{print $1}'