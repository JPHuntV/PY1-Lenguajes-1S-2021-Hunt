/*Tabla aula*/
CREATE TABLE `Aulas` (
  `nombre` varchar(4) NOT NULL,
  `capacidad` int NOT NULL,
  PRIMARY KEY (`nombre`),
  UNIQUE KEY `Aulascol_UNIQUE` (`nombre`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*******************************************************************/

/*Tabla cursos*/
CREATE TABLE `Cursos` (
  `codigoCurso` varchar(6) NOT NULL,
  `codigoCarrera` varchar(2) NOT NULL,
  `nombre` varchar(50) NOT NULL,
  PRIMARY KEY (`codigoCurso`),
  UNIQUE KEY `idCurso_UNIQUE` (`codigoCurso`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*********************************************************************/

/*Tabla Profesor*/
CREATE TABLE `Profesor` (
  `cedula` int NOT NULL,
  `nombre` varchar(50) NOT NULL,
  PRIMARY KEY (`cedula`),
  UNIQUE KEY `cedula_UNIQUE` (`cedula`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/******************************************************************/


CREATE TABLE `CursosXPeriodo` (
  `idCursoXPeriodo` int NOT NULL AUTO_INCREMENT,
  `codigoCurso` varchar(6) NOT NULL,
  `anio` int NOT NULL,
  `periodo` int NOT NULL,
  `grupo` int NOT NULL,
  `cedulaProfesor` int NOT NULL,
  `cantidadEstudiantes` int NOT NULL,
  PRIMARY KEY (`idCursoXPeriodo`),
  UNIQUE KEY `idCursoXPeriodo_UNIQUE` (`idCursoXPeriodo`),
  KEY `fk_CursosXPeriodo_1_idx` (`codigoCurso`),
  KEY `fk_CursosXPeriodo_1_idx1` (`cedulaProfesor`),
  CONSTRAINT `fk_codigoCurso` FOREIGN KEY (`codigoCurso`) REFERENCES `Cursos` (`codigoCurso`),
  CONSTRAINT `fk_profesor` FOREIGN KEY (`cedulaProfesor`) REFERENCES `Profesor` (`cedula`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;





insert into Cursos (codigoCurso, codigoCarrera, nombre)
values("IC4700", "IC", "Lenguajes De Programación"),
		("IC5701","IC", "Compiladores E interpretes"),
        ("IC1803","IC","Taller De Programación"),
        ("IC1802","IC","Introducción a la programación"),
        ("IC3002", "IC","Análisis De Algoritmos"),
        ("IC4301","IC","Bases De Datos"),
        ("AE1219","AE","Introducción a la administración de empresas"),
        ("AE3505","AE","Metodología de la investigación"),
        ("AE1122","AE","Contabilidad I"),
        ("PI3501","PI","Costos Industriales I"),
        ("PI3502","PI","Costos Industriales II"),
        ("PI2610","PI","Probabilidad y Estadistica I"),
        ("EL3212","EL","Circuitos discretos"),
        ("EL4702","EL","Probabilidad y Estadística I"),
        ("EL4703","EL","Señales y sistemas");
        

DROP procedure IF EXISTS `insertAula`;

DELIMITER $$
USE `gestionDeAulas`$$
CREATE PROCEDURE `insertAula` (in pNombre varchar(4), in pCapacidad int)
BEGIN
	insert into Aulas (nombre, capacidad)
		values(pNombre, pCapacidad);
END$$

DELIMITER ;


        
DROP procedure IF EXISTS `insertProfesor`;

DELIMITER $$
USE `gestionDeAulas`$$
CREATE PROCEDURE `insertProfesor` (in pCedula INT, in pNombre varchar(50))
BEGIN
	insert into Profesor (cedula, nombre)
		values(pCedula, pNombre);
END$$

DELIMITER ;


DROP procedure IF EXISTS `getInfoProfesores`;

DELIMITER $$
USE `gestionDeAulas`$$
CREATE PROCEDURE `getInfoProfesores` ()
BEGIN
	select * from Profesor;
END$$

DELIMITER ;


DROP procedure IF EXISTS `delProfesores`;

DELIMITER $$
USE `gestionDeAulas`$$
CREATE PROCEDURE `delProfesores` ()
BEGIN
	delete from Profesor;
END$$

DELIMITER ;

DROP procedure IF EXISTS `getInfoCursos`;

DELIMITER $$
USE `gestionDeAulas`$$
CREATE PROCEDURE `getInfoCursos` ()
BEGIN
	select * from Cursos;
END$$

DELIMITER ;

DROP procedure IF EXISTS `insertCursoXPeriodo`;

DELIMITER $$
USE `gestionDeAulas`$$
CREATE PROCEDURE `insertCursoXPeriodo` (in pCodigoCurso varchar(6), in pAnio int, in pPeriodo int, in pGrupo int,
										in pCedulaProfesor int, in pCantidadEstudiantes int )
BEGIN
	insert into CursosXPeriodo(codigoCurso, anio, periodo, grupo, cedulaProfesor, cantidadEstudiantes)
						values(pCodigoCurso, pAnio, pPeriodo, pGrupo, pCedulaProfesor, pCantidadEstudiantes);
END$$

DELIMITER ;


DROP procedure IF EXISTS `getInfoCursosXPeriodo`;

DELIMITER $$
USE `gestionDeAulas`$$
CREATE PROCEDURE `getInfoCursosXPeriodo` ()
BEGIN
	select cp.codigoCurso,c.nombre, cp.anio, cp.periodo, cp.grupo, cp.cedulaProfesor, p.nombre, cp.cantidadEstudiantes
    from CursosXPeriodo cp
    inner join Cursos c on c.codigoCurso = cp.codigoCurso
    inner join Profesor p on p.cedula = cp.cedulaProfesor;
END$$

DELIMITER ;

DROP procedure IF EXISTS `delInfoCursosXPeriodoById`;

DELIMITER $$
USE `gestionDeAulas`$$
CREATE PROCEDURE `delInfoCursosXPeriodoById` (in pId int)
BEGIN
	delete from CursosXPeriodo
    where idCursoXPeriodo = pId;
END$$

DELIMITER ;


select * from Aulas


