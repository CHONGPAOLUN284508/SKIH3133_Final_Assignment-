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

// Get sensor data from POST request
$avgTemperature = $_POST['avgTemperature'];
$avgHumidity = $_POST['avgHumidity'];
$avgDistance = $_POST['avgDistance'];
$avgLight = $_POST['avgLight'];
$minTemperature = $_POST['minTemperature'];
$minHumidity = $_POST['minHumidity'];
$minDistance = $_POST['minDistance'];
$minLight = $_POST['minLight'];
$maxTemperature = $_POST['maxTemperature'];
$maxHumidity = $_POST['maxHumidity'];
$maxDistance = $_POST['maxDistance'];
$maxLight = $_POST['maxLight'];
$relay = $_POST['relay'];

// Prepare an SQL statement for execution
$stmt = $conn->prepare("INSERT INTO readings (avgTemperature, avgHumidity, avgDistance, avgLight, minTemperature, minHumidity, minDistance, minLight, maxTemperature, maxHumidity, maxDistance, maxLight, relay) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");

// Check if the statement preparation failed and display an error message if it did
if ($stmt === false) {
    die("Prepare failed: " . $conn->error);
}

// Bind parameters to the SQL statement
// "ddiddiddiddis" specifies the types of the parameters: d = double, i = integer, s = string
$stmt->bind_param("ddiddiddiddis", $avgTemperature, $avgHumidity, $avgDistance, $avgLight, $minTemperature, $minHumidity, $minDistance, $minLight, $maxTemperature, $maxHumidity, $maxDistance, $maxLight, $relay);

// Execute the SQL statement and check if it was successful
if ($stmt->execute()) {
    echo "New record created successfully"; // Success message
} else {
    echo "Error: " . $stmt->error; // Error message
}

// Close the statement
$stmt->close();
// Close the database connection
$conn->close();
?>
