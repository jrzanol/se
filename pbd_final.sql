/*	Sistema de Entregas.
	Grupo 7 - Ronei Â. Zanol Júnior.
*/

/* Limpa o Banco de Dados. */
DROP SCHEMA pbd;
CREATE SCHEMA pbd;

/* Cria as tabelas. */
CREATE TABLE pbd.Usuario (
    CPF VARCHAR(32) NOT NULL UNIQUE,
    Nome VARCHAR(128),
    Endereco VARCHAR(128),
    Telefone VARCHAR(32),
    TipoUsuario INTEGER,
    codigoCentro VARCHAR(8),
    PRIMARY KEY(CPF)
);

CREATE TABLE pbd.Centro (
    Codigo VARCHAR(8) UNIQUE,
    Endereco VARCHAR(128),
    Cidade VARCHAR(32),
    Estado VARCHAR(32),
    Telefone VARCHAR(32),
	PRIMARY KEY(Codigo)
);

CREATE TABLE pbd.Transporte (
    DataSaida DATE,
    codigoCentro VARCHAR(8),
    cpfMotorista VARCHAR(32),
	PRIMARY KEY(DataSaida)
);

CREATE TABLE pbd.Objetos (
    Codigo VARCHAR(32) UNIQUE,
    Nome VARCHAR(128),
    Telefone VARCHAR(32),
    Endereco VARCHAR(128),
    Cidade VARCHAR(32),
    Estado VARCHAR(32),
    DataPedido DATE,
    EndereçoDestino VARCHAR(128),
    CidadeDestino VARCHAR(32),
    EstadoDestino VARCHAR(32),
	PRIMARY KEY(Codigo)
);

CREATE TABLE pbd.Transporte_Objetos (
    dataSaidaTransporte DATE,
    codigoObjeto VARCHAR(32),
    codigoCentro VARCHAR(8)
);

CREATE TABLE pbd.Despacho (
    cpfUsuario VARCHAR(32),
    codigoCentro VARCHAR(8),
    codigoObjeto VARCHAR(32),
    EntradaSaida BOOLEAN,
    Data DATE,
    CpfRg VARCHAR(32),
	PRIMARY KEY(EntradaSaida)
);

/* Define as chaves estrangeiras. */
ALTER TABLE pbd.Usuario ADD CONSTRAINT FK_Usuario_1 FOREIGN KEY (codigoCentro) REFERENCES pbd.Centro(Codigo);
 
ALTER TABLE pbd.Transporte ADD CONSTRAINT FK_Transporte_1 FOREIGN KEY (cpfMotorista) REFERENCES pbd.Usuario (CPF);
ALTER TABLE pbd.Transporte ADD CONSTRAINT FK_Transporte_2 FOREIGN KEY (codigoCentro) REFERENCES pbd.Centro (Codigo);

ALTER TABLE pbd.Transporte_Objetos ADD CONSTRAINT FK_Transporte_Objetos_1 FOREIGN KEY (dataSaidaTransporte) REFERENCES pbd.Transporte (DataSaida);
ALTER TABLE pbd.Transporte_Objetos ADD CONSTRAINT FK_Transporte_Objetos_2 FOREIGN KEY (codigoObjeto) REFERENCES pbd.Objetos (Codigo);
ALTER TABLE pbd.Transporte_Objetos ADD CONSTRAINT FK_Transporte_Objetos_3 FOREIGN KEY (codigoCentro) REFERENCES pbd.Centro (Codigo);
 
ALTER TABLE pbd.Despacho ADD CONSTRAINT FK_Despacho_1 FOREIGN KEY (cpfUsuario) REFERENCES pbd.Usuario (CPF);
ALTER TABLE pbd.Despacho ADD CONSTRAINT FK_Despacho_2 FOREIGN KEY (codigoCentro) REFERENCES pbd.Centro (Codigo);
ALTER TABLE pbd.Despacho ADD CONSTRAINT FK_Despacho_3 FOREIGN KEY (codigoObjeto) REFERENCES pbd.Objetos (Codigo);

