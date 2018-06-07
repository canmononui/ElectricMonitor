<?php
include 'connect.php';
$amp_all = 1;
$amp_air = 1;
$amp_water = 1;
$amp_light = 1;
$amp_plug = 1;
$sql = "INSERT INTO sensor`(id`, time, amp_all, amp_air, amp_water, amp_light, amp_plug)";
$sql .= "VALUES ("."NULL".",'"."CURRENT_TIMESTAMP"."','".$amp_all."','".$amp_air."','".$amp_water."','".$amp_light."','".$amp_plug."')";
if($conn->query($sql))
{
    echo "OK";
}
$conn->close();
?>