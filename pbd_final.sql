/*	Sistema de Entregas.
	Grupo 7 - Ronei Â. Zanol Júnior.
*/

/* Limpa o Banco de Dados. */
DROP SCHEMA pbd;
CREATE SCHEMA pbd;

/* Cria as tabelas. */
CREATE TABLE pbd.Centro (
    Codigo VARCHAR(8) UNIQUE,
    Endereco VARCHAR(128),
    Cidade VARCHAR(32),
    Estado VARCHAR(32),
    Telefone VARCHAR(32),
	PRIMARY KEY(Codigo)
);

CREATE TABLE pbd.Distancia_Centro (
    codigoCentro1 VARCHAR(8),
    codigoCentro2 VARCHAR(8),
	Distancia INTEGER,
	FOREIGN KEY(codigoCentro1) REFERENCES pbd.Centro(Codigo),
	FOREIGN KEY(codigoCentro2) REFERENCES pbd.Centro(Codigo)
);

CREATE TABLE pbd.Usuario (
    CPF VARCHAR(32) NOT NULL UNIQUE,
    Senha VARCHAR(32),
    Nome VARCHAR(128),
    Endereco VARCHAR(128),
    Telefone VARCHAR(32),
    TipoUsuario INTEGER,
    codigoCentro VARCHAR(8),
    PRIMARY KEY(CPF),
	FOREIGN KEY(codigoCentro) REFERENCES pbd.Centro(Codigo)
);

CREATE TABLE pbd.Transporte (
	Saida BOOLEAN,
    DataSaida DATETIME,
    codigoCentro VARCHAR(8),
    cpfMotorista VARCHAR(32),
	PRIMARY KEY(Saida, DataSaida),
	FOREIGN KEY(cpfMotorista) REFERENCES pbd.Usuario (CPF),
	FOREIGN KEY(codigoCentro) REFERENCES pbd.Centro (Codigo)
);

CREATE TABLE pbd.Objetos (
    Codigo VARCHAR(32) UNIQUE,
    Nome VARCHAR(128),
    Telefone VARCHAR(32),
    Endereco VARCHAR(128),
    Cidade VARCHAR(32),
    Estado VARCHAR(32),
    codigoCentro VARCHAR(8),
    DataPedido DATETIME,
    EndereçoDestino VARCHAR(128),
    CidadeDestino VARCHAR(32),
    EstadoDestino VARCHAR(32),
	PRIMARY KEY(Codigo),
	FOREIGN KEY(codigoCentro) REFERENCES pbd.Centro(Codigo)
);

CREATE TABLE pbd.Transporte_Objetos (
	saida BOOLEAN,
    dataSaidaTransporte DATETIME,
    codigoObjeto VARCHAR(32),
    codigoCentro VARCHAR(8),
	FOREIGN KEY(saida, dataSaidaTransporte) REFERENCES pbd.Transporte (Saida, DataSaida),
	FOREIGN KEY(codigoObjeto) REFERENCES pbd.Objetos (Codigo),
	FOREIGN KEY(codigoCentro) REFERENCES pbd.Centro (Codigo)
);

CREATE TABLE pbd.Despacho (
    cpfUsuario VARCHAR(32),
    codigoCentro VARCHAR(8),
    codigoObjeto VARCHAR(32),
    EntradaSaida BOOLEAN,
    Data DATETIME,
    CpfRg VARCHAR(32),
	FOREIGN KEY(cpfUsuario) REFERENCES pbd.Usuario (CPF),
	FOREIGN KEY(codigoCentro) REFERENCES pbd.Centro (Codigo),
	FOREIGN KEY(codigoObjeto) REFERENCES pbd.Objetos (Codigo)
);

/* Inserção dos dados. */
INSERT INTO pbd.centro VALUES ('RS01', 'Centro, 152', 'Pelotas', 'RS', '(53) 3222-5678');
INSERT INTO pbd.centro VALUES ('SC01', 'Centro, 152', 'Florianopolis', 'SC', '(48) 3222-5678');
INSERT INTO pbd.centro VALUES ('PR01', 'Centro, 152', 'Curitiba', 'PR', '(44) 3222-5678');
INSERT INTO pbd.centro VALUES ('SP01', 'Centro, 152', 'Sao Paulo', 'SP', '(11) 3222-5678');
INSERT INTO pbd.centro VALUES ('RJ01', 'Centro, 152', 'Rio de Janeiro', 'RJ', '(11) 3222-5678');

INSERT INTO pbd.Distancia_Centro VALUES ('RS01', 'SC01', 713);
INSERT INTO pbd.Distancia_Centro VALUES ('RS01', 'PR01', 992);
INSERT INTO pbd.Distancia_Centro VALUES ('RS01', 'SP01', 1340);
INSERT INTO pbd.Distancia_Centro VALUES ('RS01', 'RJ01', 1820);
INSERT INTO pbd.Distancia_Centro VALUES ('SC01', 'PR01', 306);
INSERT INTO pbd.Distancia_Centro VALUES ('SC01', 'SP01', 694);
INSERT INTO pbd.Distancia_Centro VALUES ('SC01', 'RJ01', 1134);
INSERT INTO pbd.Distancia_Centro VALUES ('PR01', 'SP01', 416);
INSERT INTO pbd.Distancia_Centro VALUES ('PR01', 'RJ01', 856);
INSERT INTO pbd.Distancia_Centro VALUES ('SP01', 'RJ01', 434);

INSERT INTO pbd.usuario VALUES ('000-111-222-01', 'admin', 'Jose', 'Laranjal, 100', '(53) 99245-1234', 0, 'RS01');
INSERT INTO pbd.usuario VALUES ('000-111-222-02', 'admin', 'Aline', 'Laranjal, 100', '(53) 99245-1234', 1, 'RS01');
INSERT INTO pbd.usuario VALUES ('000-111-222-03', 'admin', 'Jorge', 'Laranjal, 100', '(53) 99245-1234', 1, 'RS01');
INSERT INTO pbd.usuario VALUES ('000-111-222-04', 'admin', 'Pedro', 'Laranjal, 100', '(53) 99245-1234', 1, 'RS01');
INSERT INTO pbd.usuario VALUES ('000-111-222-05', 'admin', 'Roberto', 'Laranjal, 100', '(53) 99245-1234', 1, 'RS01');
INSERT INTO pbd.usuario VALUES ('000-111-222-06', 'admin', 'Fabricio', 'Laranjal, 100', '(53) 99245-1234', 1, 'RS01');

INSERT INTO pbd.objetos VALUES ('OB0000000000', 'Alberto', '(53) 99122-5647', 'Centro, 8', 'Pelotas', 'RS', 'SC01', '2023-08-01 08:30:00', 'Centro, 123', 'Florianopolis', 'SC');
INSERT INTO pbd.objetos VALUES ('OB0011223345', 'Pedro', '(53) 99122-5647', 'Centro, 8', 'Pelotas', 'RS', 'RS01', '2023-08-01 08:30:00', 'Centro, 123', 'Florianopolis', 'SC');
INSERT INTO pbd.objetos VALUES ('OB0011223346', 'Pedro', '(53) 99122-5647', 'Centro, 8', 'Pelotas', 'RS', 'RS01', '2023-08-01 08:30:00', 'Centro, 123', 'Florianopolis', 'SC');
INSERT INTO pbd.objetos VALUES ('OB0011223347', 'Pedro', '(53) 99122-5647', 'Centro, 8', 'Pelotas', 'RS', 'RS01', '2023-08-01 08:30:00', 'Centro, 123', 'Florianopolis', 'SC');
INSERT INTO pbd.objetos VALUES ('OB0011223348', 'Abel', '(53) 99122-5641', 'Centro, 8', 'Pelotas', 'RS', 'RS01', '2023-08-05 08:00:00', 'Centro, 55', 'Curitiba', 'PR');
INSERT INTO pbd.objetos VALUES ('OB0011223349', 'Abel', '(53) 99122-5641', 'Centro, 8', 'Pelotas', 'RS', 'RS01', '2023-08-05 08:00:00', 'Centro, 55', 'Curitiba', 'PR');
INSERT INTO pbd.objetos VALUES ('OB0011223350', 'Abel', '(53) 99122-5641', 'Centro, 8', 'Pelotas', 'RS', 'RS01', '2023-08-05 08:00:00', 'Centro, 55', 'Curitiba', 'PR');
INSERT INTO pbd.objetos VALUES ('OB0011223351', 'Abel', '(53) 99122-5641', 'Centro, 8', 'Pelotas', 'RS', 'RS01', '2023-08-05 08:00:00', 'Centro, 55', 'Curitiba', 'PR');

INSERT INTO pbd.Transporte VALUES (true, '2023-08-05 08:30:00', 'RS01', '000-111-222-02');
INSERT INTO pbd.Transporte VALUES (false, '2023-08-05 08:30:00', 'SP01', '000-111-222-02');
INSERT INTO pbd.Transporte VALUES (true, '2023-08-09 08:30:00', 'RS01', '000-111-222-03');
INSERT INTO pbd.Transporte VALUES (false, '2023-08-09 08:30:00', 'SC01', '000-111-222-03');
INSERT INTO pbd.Transporte VALUES (true, '2023-08-01 08:30:00', 'RS01', '000-111-222-04');
INSERT INTO pbd.Transporte VALUES (false, '2023-08-01 08:30:00', 'PR01', '000-111-222-04');
INSERT INTO pbd.Transporte VALUES (true, '2023-08-07 08:30:00', 'SC01', '000-111-222-05');
INSERT INTO pbd.Transporte VALUES (false, '2023-08-07 08:30:00', 'RS01', '000-111-222-05');
INSERT INTO pbd.Transporte VALUES (true, '2023-08-10 08:30:00', 'PR01', '000-111-222-06');
INSERT INTO pbd.Transporte VALUES (false, '2023-08-10 08:30:00', 'RS01', '000-111-222-06');

