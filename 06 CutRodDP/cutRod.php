<!DOCTYPE html>
<html>
<body>

<?php
$n = 50;
$priceList = array(0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30);
$dp = [];
for ($i = 0; $i < $n; $i++) {
	$dp[] = null;
}

function f($n) {
	global $dp, $priceList;
	if ($n == 1) return $n;
    if ($dp[$n] != null) return $dp[$n];
    $maxPrice = $priceList[$n];
    for($i = 1; $i < $n; $i++){
    	$subResult = f($n-$i);
        if ($maxPrice < $priceList[$i] + $subResult)
        	$maxPrice = $priceList[$i] + $subResult;
    }
    $dp[$n] = $maxPrice;
    return $dp[$n];
}

for ($i = 1; $i < $n; $i++) {
  $result = f($i);
  echo 'Length: ';
  echo $i;
  echo ' = ';
  echo $result;
  echo '<br/>';
}
?> 

</body>
</html>
