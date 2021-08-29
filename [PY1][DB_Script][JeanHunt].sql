SELECT * FROM gestionDeAulas.Cursos;


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


DROP procedure IF EXISTS `getInfoCursos`;

DELIMITER $$
USE `gestionDeAulas`$$
CREATE PROCEDURE `getInfoCursos` ()
BEGIN
	select * from Cursos;
END$$

DELIMITER ;

call getInfoCursos();



