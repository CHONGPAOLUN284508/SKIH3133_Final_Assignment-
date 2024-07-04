-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Jul 03, 2024 at 03:21 PM
-- Server version: 10.4.28-MariaDB
-- PHP Version: 8.0.28

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `assignment3`
--

-- --------------------------------------------------------

--
-- Table structure for table `readings`
--

CREATE TABLE `readings` (
  `id` int(11) NOT NULL,
  `avgTemperature` float DEFAULT NULL,
  `avgHumidity` float DEFAULT NULL,
  `avgDistance` float DEFAULT NULL,
  `avgLight` float DEFAULT NULL,
  `minTemperature` float DEFAULT NULL,
  `minHumidity` float DEFAULT NULL,
  `minDistance` float DEFAULT NULL,
  `minLight` float DEFAULT NULL,
  `maxTemperature` float DEFAULT NULL,
  `maxHumidity` float DEFAULT NULL,
  `maxDistance` float DEFAULT NULL,
  `maxLight` float DEFAULT NULL,
  `relay` varchar(3) DEFAULT NULL,
  `timestamp` timestamp NOT NULL DEFAULT current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `readings`
--

INSERT INTO `readings` (`id`, `avgTemperature`, `avgHumidity`, `avgDistance`, `avgLight`, `minTemperature`, `minHumidity`, `minDistance`, `minLight`, `maxTemperature`, `maxHumidity`, `maxDistance`, `maxLight`, `relay`, `timestamp`) VALUES
(76, 30.33, 78, 5, 9.72, 30.3, 78, 5, 9.17, 30, 78, 5, 10, 'ON', '2024-07-03 12:35:12'),
(77, 30.35, 77.83, 5, 9.86, 30.3, 77, 5, 9.17, 30, 78, 5, 10, 'ON', '2024-07-03 12:35:42'),
(78, 30.37, 77.67, 5, 9.86, 30.3, 77, 5, 9.17, 30, 78, 5, 10, 'ON', '2024-07-03 12:36:12'),
(79, 30.38, 77.5, 5, 9.86, 30.3, 77, 5, 9.17, 30, 78, 5, 10, 'ON', '2024-07-03 12:36:42'),
(80, 30.4, 77.33, 5, 10, 30.4, 77, 5, 10, 30, 78, 5, 10, 'ON', '2024-07-03 12:37:12'),
(81, 30.4, 77.17, 5, 10, 30.4, 77, 5, 10, 30, 78, 5, 10, 'ON', '2024-07-03 12:37:43');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `readings`
--
ALTER TABLE `readings`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `readings`
--
ALTER TABLE `readings`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=82;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
