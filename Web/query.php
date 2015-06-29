<?php
	$connection = mysql_connect("snowwolf725.jjvk.com", "snowwolf_ir", "ir");
	if(!$connection)
		die("Could not connect to database server: " . mysql_error());
	if(!mysql_select_db("snowwolf_ir", $connection))
		die("Could not use database : experiment");
	mysql_query("SET NAMES 'utf8'", $connection); 
?>
<html>
<head>
<script language=JavaScript>
function lastTen(currentIndex){
	if(currentIndex == 0) {
		alert("First page.");
	} else {
		document.forms.queryForm.startIndex.value = parseInt(currentIndex) - 10;
		document.forms.queryForm.submit();
	}
}
function nextTen(currentIndex){
	if(parseInt(currentIndex) + 10 > document.forms.totalForm.total.value) {
		alert("Last page.");
	} else {
		document.forms.queryForm.startIndex.value = parseInt(currentIndex) + 10;
		document.forms.queryForm.submit();
	}
}
	
</script>

<title>FTP Searching File System</title>
</head>
<body>
<center>
<h1>FTP Searching File System</h1>
<form name="queryForm" action="query.php" method="post">
	<table border=0>
		<tr>
			<td>Key Word:</td>
			<td><input type="text" name="keyWord" size="20" value="<?php echo $_POST["keyWord"];?>"></td>
		</tr>
		<tr>
			<td>File Name:</td>
			<td><input type="text" name="fileName" size="20" value="<?php echo $_POST["fileName"];?>"></td>
		</tr>
		<tr>
			<td>Extension Name:</td>
			<td><input type="text" name="extName" size="20" value="<?php echo $_POST["extName"];?>"></td>
		</tr>
		<tr>
			<td>Start Date:</td>
			<td><input type="text" name="startDate" size="20" value="<?php echo $_POST["startDate"];?>"></td>
		</tr>
		<tr>
			<td>End Date:</td>
			<td><input type="text" name="endDate" size="20" value="<?php echo $_POST["endDate"];?>"></td>
		</tr>
	</table>
	<input type="submit" value="Query">
	<input type="hidden" name="startQuery" value="1">
	<input type="hidden" name="startIndex" value="0">
</form>
<hr>

<?php
function getParentID($docid)
{
	// get parent id
	$sql = "select parentid from index_table where id=".$docid;
	$result = mysql_query($sql) or die ("Invalid query");
	if($row = mysql_fetch_array($result))
	{
		$parentid = $row["parentid"];
		return $parentid;
	}
	else
		return 0;
}

function getDocScore($docid,$token)
{
	$relatedsql = "select docid from doc_index where docid=".$docid." and token like '%".$token."%' or 1=2";
	$relatedresult = mysql_query($relatedsql) or die ("Invalid query");
	$relatedtotal = mysql_num_rows($relatedresult);
	
	$relatedsql = "select docid from doc_index where docid=".$docid;
	$relatedresult = mysql_query($relatedsql) or die ("Invalid query");
	$total = mysql_num_rows($relatedresult);
	
	return $relatedtotal;
	//return doubleval($relatedtotal/$total);
}

	if($_POST["startQuery"] == 1){
		echo "<h1>Query Result</h1><br>";
		
		$sql = "select * from index_table where ";
		if($_POST["fileName"] != "")
			$sql = $sql. " name like '%".$_POST["fileName"]."%' and";

		if($_POST["extName"] != "")
			$sql = $sql. " extName like '%".$_POST["extName"]."%' and";
		if($_POST["startDate"] != "" && $_POST["endDate"] != "")
			$sql = $sql. " date between '".$_POST["startDate"]."' and '".$_POST["endDate"]."' and ";
		else if($_POST["startDate"] != "")
			$sql = $sql. " date > '".$_POST["startDate"]."' and";
		else if($_POST["endDate"] != "")
			$sql = $sql. " date < '".$_POST["endDate"]."' and ";
		if($_POST["keyWord"])
			$sql = $sql. " (name like '%".$_POST["keyWord"]."%' or extName like '%".$_POST["keyWord"]."%' or path like '%".$_POST["keyWord"]."%') and ";	
		$sql = $sql." 1=1";
		$result = mysql_query($sql) or die ("Invalid query");
		$total = 0;
		$rank = array();
		$docparent = array();
		while(($row = mysql_fetch_array($result)))
		{
			$parentid = getParentID($row["id"]);
			$docparent[$row["id"]] = $parentid;
			$rank[$parentid] += 10;
			$searchresult[$total] = $row["id"];
			$total++;
		}
		// find match doc
		if($_POST["keyWord"]){
			$relatedsql = "select DISTINCT docid from doc_index where token like '%".$_POST["keyWord"]."%' or 1=2";
			$relatedresult = mysql_query($relatedsql) or die ("Invalid query");
			while(($row = mysql_fetch_array($relatedresult)))
			{
				$parentid = getParentID($row["docid"]);
				$docparent[$row["docid"]] = $parentid;
				$rank[$parentid] += getDocScore($row["docid"],$_POST["keyWord"]);
				$searchresult[$total] = $row["docid"];
				$total++;
			}
		}
		
		if($total == 0)
			echo "There is no result.";
		else
		{
			echo "There are ".$total." results.<br>";
		    echo "<a href='#' onClick='lastTen(\"".$_POST["startIndex"]."\")'>pre</a>&nbsp;&nbsp;&nbsp;&nbsp;";
 		    echo "<a href='#' onClick='nextTen(\"".$_POST["startIndex"]."\")'>next</a><br>";
		}
		echo '<table width="800" border="1">
			  <tr>
			  	<th scope="col">Rank</th>
				<th scope="col">Filename</th>
				<th scope="col">ExtName</th>
				<th scope="col">Size</th>
				<th scope="col">Date</th>
				<th scope="col">Desc</th>
			  </tr>';
		arsort($rank);
		$displaycount = 1;
		$isleft = 0;
		foreach ($rank as $key => $val) {
			if($isleft)
				break;
			$sql = "select * from index_table where id=".$key;
			$result = mysql_query($sql) or die ("Invalid query");
			while(($row = mysql_fetch_array($result)))
			{
				if($isleft)
					break;
				echo "<tr>";
				echo "<td>".$val."</td>";
				echo "<td><a href='".$row["path"]."'>".$row["path"]."</a></td>";
				echo "<td></td>";
				echo "<td></td>";
				echo "<td>".$row["date"]."</td>";
				echo "<td></td>";
				echo "</tr>\n";
				foreach ($docparent as $docparentkey => $docparentval) {
					if($docparentval == $key)
					{
						if($displaycount <= $_POST["startIndex"])
						{
							$displaycount++;
							continue;
						}
						else if($displaycount > $_POST["startIndex"]+10)
						{
							$isleft = 1;
							break;
						}
						else
							$displaycount++;
						$docsql = "select * from index_table where id=".$docparentkey;
						$docresult = mysql_query($docsql) or die ("Invalid query");
						while(($docrow = mysql_fetch_array($docresult)))
						{
							echo "<tr>";
							echo "<td> </td>";
							echo "<td><a href='".$docrow["path"]."'>".$docrow["name"]."</a></td>";
							echo "<td>".$docrow["extName"]."</td>";
							echo "<td>".$docrow["size"]."</td>";
							echo "<td>".$docrow["date"]."</td>";
							echo "<td>".$docrow["desc"]."</td>";
							echo "</tr>\n";
						}
					}
				}
			}

		}
		echo '</table>';
		echo "<form name='totalForm'>";
		echo "<input type=hidden name=total value=".$total.">";
		echo "</form>";
	}
?>
</center>
</body>
</html>
