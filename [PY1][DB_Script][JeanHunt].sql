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


CREATE TABLE `Reservas` (
  `codigoReserva` int NOT NULL AUTO_INCREMENT,
  `fecha` date NOT NULL,
  `horaInicio` time NOT NULL,
  `horaFin` time NOT NULL,
  `nombreAula` varchar(4) NOT NULL,
  `anio` int NOT NULL,
  `periodo` int NOT NULL,
  `codigoCurso` varchar(6) NOT NULL,
  `grupo` int NOT NULL,
  PRIMARY KEY (`codigoReserva`),
  UNIQUE KEY `codigoReserva_UNIQUE` (`codigoReserva`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;




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


DROP procedure IF EXISTS `getInfoCursosXPeriodoByAnio`;

DELIMITER $$
USE `gestionDeAulas`$$
CREATE PROCEDURE `getInfoCursosXPeriodoByAnio` (in pAnio int, in pPeriodo int)
BEGIN
	select cp.codigoCurso,c.nombre, cp.anio, cp.periodo, cp.grupo, p.nombre, cp.cantidadEstudiantes
    from CursosXPeriodo cp
    inner join Cursos c on c.codigoCurso = cp.codigoCurso
    inner join Profesor p on p.cedula = cp.cedulaProfesor
    where cp.anio = pAnio and cp.periodo = pPeriodo;
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


DROP procedure IF EXISTS `getAulasAforo`;

DELIMITER $$
USE `gestionDeAulas`$$
CREATE PROCEDURE `getAulasAforo` (in pFecha Date, in pInicio Time, in pFin Time, in pCantidadEstudiantes int )
BEGIN
	select * from Aulas
    where nombre not in
    (
	select a.nombre
    from Aulas a
    inner join Reservas r on a.nombre = r.nombreAula
    where r.fecha = pFecha and (r.horaInicio between pInicio and pFin
    or r.horaFin between pInicio and pFin)
    )
    and capacidad>= pCantidadEstudiantes;
END$$

DELIMITER ;



DROP procedure IF EXISTS `insertReserva`;

DELIMITER $$
USE `gestionDeAulas`$$
CREATE PROCEDURE `insertReserva` (in pFecha date, in pHorainicio Time, in pHoraFin Time, in pNombreAula varchar(4),
					in pAnio int, in pPeriodo int, in pCodigoCurso varchar(6), in pGrupo int)
BEGIN
	insert into Reservas (fecha, horaInicio, horaFin, nombreAula, anio, periodo, codigoCurso, grupo)
		values(pFecha, pHoraInicio, pHoraFin, pNombreAula, pAnio, pPeriodo, pCodigoCurso, pGrupo);
	
    select * from Reservas order by codigoReserva DESC limit 1;
END$$

DELIMITER ;

DROP procedure IF EXISTS `getReserva`;

DELIMITER $$
USE `gestionDeAulas`$$
CREATE PROCEDURE `getReserva` (in pCodigoReserva int)
BEGIN
	select * from Reservas
    where codigoReserva = pCodigoReserva;
END$$

DELIMITER ;


DROP procedure IF EXISTS `deleteReserva`;

DELIMITER $$
USE `gestionDeAulas`$$
CREATE PROCEDURE `deleteReserva` (in pCodigoReserva int)
BEGIN
	delete from Reservas
    where codigoReserva = pCodigoReserva;
END$$

DELIMITER ;




DROP procedure IF EXISTS `topAulas`;

DELIMITER $$
USE `gestionDeAulas`$$
CREATE PROCEDURE `topAulas` ()
BEGIN
	select  nombreAula, count(nombreAula) as cantidad from Reservas
	group by nombreAula
	order by cantidad Desc
limit 3;
END$$

DELIMITER ;



DROP procedure IF EXISTS `topProfesores`;

DELIMITER $$
USE `gestionDeAulas`$$
CREATE PROCEDURE `topProfesores` ()
BEGIN
	select p.nombre, count(p.nombre) as cantidad from Reservas r
	inner join Cursos c on c.codigoCurso = r.codigoCurso
	inner join CursosXPeriodo per on per.codigoCurso = c.codigoCurso
	inner join Profesor p on p.cedula = per.cedulaProfesor
	group by p.nombre
	order by cantidad Desc
limit 3;
END$$

DELIMITER ;


DROP procedure IF EXISTS `reservasMesAnio`;

DELIMITER $$
USE `gestionDeAulas`$$
CREATE PROCEDURE `reservasMesAnio` ()
BEGIN
	select month(fecha), year(fecha) ,count(*) as cantidad from Reservas
	group by month(fecha), year(fecha);
END$$

DELIMITER ;


DROP procedure IF EXISTS `getReservasByAula`;

DELIMITER $$
USE `gestionDeAulas`$$
CREATE PROCEDURE `getReservasByAula` (in pAula varchar(4))
BEGIN
	select * from Reservas
    where nombreAula = pAula;
END$$

DELIMITER ;


DROP procedure IF EXISTS `getReservasByCurso`;

DELIMITER $$
USE `gestionDeAulas`$$
CREATE PROCEDURE `getReservasByCurso` (in pAnio int, in pPeriodo int, in pCodigoCurso varchar(6), in pGrupo int)
BEGIN
	select codigoReserva, fecha, horaInicio, horaFin, nombreAula from Reservas
    where anio = pAnio and periodo = pPeriodo and codigoCurso = pCodigoCurso and grupo = pGrupo
    order by fecha and horaInicio and nombreAula asc;
END$$

DELIMITER ;



DROP procedure IF EXISTS `getReservasByDia`;

DELIMITER $$
USE `gestionDeAulas`$$
CREATE PROCEDURE `getReservasByDia` (in pFecha date)
BEGIN
	select a.nombre, r.codigoReserva, r.anio, r.periodo, r.codigoCurso, r.grupo, r.horaInicio, r.horaFin
	from Aulas a
	left join 
    (
		select * from Reservas
		where fecha = pFecha
    ) r on a.nombre = r.nombreAula;
END$$

DELIMITER ;



