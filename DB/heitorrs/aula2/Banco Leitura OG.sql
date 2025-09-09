CREATE TABLE macheitorrs (
  idmacheitorrs VARCHAR(17)  NOT NULL  ,
  Nome VARCHAR(50)  NOT NULL  ,
  contador INTEGER UNSIGNED  NULL DEFAULT 0 ,
  ativo BOOL  NULL    ,
PRIMARY KEY(idmacheitorrs));



CREATE TABLE leituraheitorrs (
  idleituraheitorrs INTEGER UNSIGNED  NOT NULL   AUTO_INCREMENT,
  macheitorrs_idmacheitorrs VARCHAR(17)  NOT NULL  ,
  datatime DATETIME  NULL  ,
  umidade REAL  NULL  ,
  temperatura REAL  NULL    ,
PRIMARY KEY(idleituraheitorrs)  ,
INDEX leituraheitorrs_FKIndex1(macheitorrs_idmacheitorrs),
  FOREIGN KEY(macheitorrs_idmacheitorrs)
    REFERENCES macheitorrs(idmacheitorrs)
      ON DELETE NO ACTION
      ON UPDATE NO ACTION);




