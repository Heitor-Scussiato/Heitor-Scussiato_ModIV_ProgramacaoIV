-- phpMyAdmin SQL Dump
-- version 5.2.0
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Tempo de geração: 09-Set-2025 às 20:17
-- Versão do servidor: 10.4.27-MariaDB
-- versão do PHP: 8.0.25

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Banco de dados: `bancoleitura`
--

DELIMITER $$
--
-- Procedimentos
--
CREATE DEFINER=`root`@`localhost` PROCEDURE `validamacheitorrs` (IN `$macheitorrs` VARCHAR(17), OUT `$ativo` BOOLEAN)   BEGIN
SELECT ativo into $ativo from macheitorrs
where idmacheitorrs = $macheitorrs;
END$$

DELIMITER ;

-- --------------------------------------------------------

--
-- Estrutura da tabela `leituraheitorrs`
--

CREATE TABLE `leituraheitorrs` (
  `idleituraheitorrs` int(10) UNSIGNED NOT NULL,
  `macheitorrs_idmacheitorrs` varchar(17) NOT NULL,
  `datatime` datetime DEFAULT NULL,
  `umidade` double DEFAULT NULL,
  `temperatura` double DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Extraindo dados da tabela `leituraheitorrs`
--

INSERT INTO `leituraheitorrs` (`idleituraheitorrs`, `macheitorrs_idmacheitorrs`, `datatime`, `umidade`, `temperatura`) VALUES
(1, '84:0D:8E:B0:82:5C', '2025-09-09 14:46:39', 93, 18.7);

--
-- Acionadores `leituraheitorrs`
--
DELIMITER $$
CREATE TRIGGER `tgcheckativoheitorrs` BEFORE INSERT ON `leituraheitorrs` FOR EACH ROW begin
CALL validamacheitorrs(new.macheitorrs_idmacheitorrs,@$ativo);
if @$ativo=0
then SIGNAL SQLSTATE '45000' SET
MESSAGE_TEXT = 'Placa inativa';
end if;
end
$$
DELIMITER ;
DELIMITER $$
CREATE TRIGGER `tgdeleteheitor` AFTER DELETE ON `leituraheitorrs` FOR EACH ROW BEGIN

UPDATE macheitorrs
set contador=contador-1

WHERE idmacheitorrs = old.macheitorrs_idmacheitorrs;

END
$$
DELIMITER ;
DELIMITER $$
CREATE TRIGGER `tginsertheitor` AFTER INSERT ON `leituraheitorrs` FOR EACH ROW BEGIN

UPDATE macheitorrs
set contador=contador+1

WHERE idmacheitorrs = new.macheitorrs_idmacheitorrs;

END
$$
DELIMITER ;

-- --------------------------------------------------------

--
-- Estrutura da tabela `macheitorrs`
--

CREATE TABLE `macheitorrs` (
  `idmacheitorrs` varchar(17) NOT NULL,
  `Nome` varchar(50) NOT NULL,
  `contador` int(10) UNSIGNED DEFAULT 0,
  `ativo` tinyint(1) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Extraindo dados da tabela `macheitorrs`
--

INSERT INTO `macheitorrs` (`idmacheitorrs`, `Nome`, `contador`, `ativo`) VALUES
('84:0D:8E:B0:82:5C', 'ESP Azul', 1, 1);

--
-- Índices para tabelas despejadas
--

--
-- Índices para tabela `leituraheitorrs`
--
ALTER TABLE `leituraheitorrs`
  ADD PRIMARY KEY (`idleituraheitorrs`),
  ADD KEY `leituraheitorrs_FKIndex1` (`macheitorrs_idmacheitorrs`);

--
-- Índices para tabela `macheitorrs`
--
ALTER TABLE `macheitorrs`
  ADD PRIMARY KEY (`idmacheitorrs`);

--
-- AUTO_INCREMENT de tabelas despejadas
--

--
-- AUTO_INCREMENT de tabela `leituraheitorrs`
--
ALTER TABLE `leituraheitorrs`
  MODIFY `idleituraheitorrs` int(10) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;

--
-- Restrições para despejos de tabelas
--

--
-- Limitadores para a tabela `leituraheitorrs`
--
ALTER TABLE `leituraheitorrs`
  ADD CONSTRAINT `leituraheitorrs_ibfk_1` FOREIGN KEY (`macheitorrs_idmacheitorrs`) REFERENCES `macheitorrs` (`idmacheitorrs`) ON DELETE NO ACTION ON UPDATE NO ACTION;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
