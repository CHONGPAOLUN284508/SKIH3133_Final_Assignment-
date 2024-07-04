<?php
$servername = "localhost"; // Database server name
$username = "root"; // Database username
$password = ""; // Database password
$dbname = "assignment3"; // Database name

// Create connection to the database
$conn = new mysqli($servername, $username, $password, $dbname);

// Check connection and display error message if connection fails
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

// SQL query to select data from the readings table, ordered by timestamp in descending order
$sql = "SELECT timestamp, avgTemperature, avgHumidity, avgDistance, avgLight, minTemperature, minHumidity, minDistance, minLight, maxTemperature, maxHumidity, maxDistance, maxLight, relay FROM readings ORDER BY timestamp DESC";
$result = $conn->query($sql);

// Check if the query execution failed and return an error message in JSON format if it did
if ($result === false) {
    die(json_encode(["error" => $conn->error]));
}

// Initialize an array to store the fetched sensor data
$sensorData = array();

// Fetch each row of the result set as an associative array and add it to the sensorData array
while ($row = $result->fetch_assoc()) {
    $sensorData[] = $row;
}

// Set the content type of the response to JSON
header('Content-Type: application/json');
// Encode the sensorData array as a JSON string and output it
echo json_encode($sensorData);

// Close the database connection
$conn->close();
?>
