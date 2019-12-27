<?php
class dht11{

 public $link='';
 function __construct($temperature){
  $this->connect();
  $this->storeInDB($temperature);
 }
 
 function connect(){
  $this->link = mysqli_connect('localhost','root','') or die('Cannot connect to the DB');
  mysqli_select_db($this->link,'shemama') or die('Cannot select the DB');
 }
 
 function storeInDB($temperature){

  $query = "insert into donnees (donne) values($temperature)";
  $result = mysqli_query($this->link,$query) or die('Errant query:  '.$query);
 }
 
}
if($_GET['temperature'] != ''){
 $dht11=new dht11($_GET['temperature']);
}
?>