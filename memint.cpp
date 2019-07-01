#include <Arduino.h>
#include <EEPROM.h> // Biblioteca para acesso e manipula��o da EEPROM

byte leByte (int endereco1){
  return EEPROM.read(endereco1); // Realizamosa leitura de 1 byte  e retornamos
}

void escreveByte (int endereco1, byte valor){ // Escreve um byte na EEPROM no endere�o especificado
  byte valorAtual = leByte(endereco1); // Lemos o byte que desejamos escrever
  if (valorAtual == valor){ // Se os valores forem iguais n�o  precisamos escrever ( economia de ciclos de escrita )
    return;
  }
  else { // Sen�o escrevemos o byte no endere�o especificado na fun��o
    EEPROM.write(endereco1,valor); // Escreve o byte no endere�o especificado na fun��o
  }

}

int lerInt(int endereco1, int endereco2){ // Le o int armazenado em dois endere�os de mem�ria
  int valor = 0; // Inicializamos nosso retorno
  byte primeiroByte = EEPROM.read(endereco1); // Leitura do primeiro byte armazenado no endere�o 1
  byte segundoByte = EEPROM.read(endereco2); // Leitura do segundo byte armazenado no endere�o 2
  valor = (segundoByte << 8) + primeiroByte; // Deslocamos o segundo byte 8 vezes para a esquerda ( formando o byte mais significativo ) e realizamos a soma com o primeiro byte ( menos significativo )
  return valor; // Retornamos o valor da leitura

}

void escreveInt(int endereco1, int endereco2, int valor){ // Escreve um inteiro de 2 bytes na EEPROM
  int valorAtual = lerInt(endereco1,endereco2); // Lemos o valor inteiro da mem�ria
  if (valorAtual == valor){ // Se o valor lido for igual ao que queremos escrever n�o � necess�rio escrever novamente
    return;
  }
  else{ // Caso contr�rio "quebramos nosso inteiro em 2 bytes e escrevemos cada byte em uma posi��o da mem�ria
      byte primeiroByte = valor&0xff; //Executamos a opera��o AND de 255 com todo o valor, o que mant�m apenas o primeiro byte
      byte segundoByte = (valor >> 8) &0xff; // Realizamos um deslocamento de 8 bits para a direita e novamente executamos um AND com o valor 255, o que retorna apenas o byte desejado
      EEPROM.write(endereco1,primeiroByte); // Copiamos o primeiro byte para o endere�o 1
      EEPROM.write(endereco2,segundoByte); // Copiamos o segundo byte para o endere�o 2
  }
}

void escreveString(int enderecoBase, String mensagem){ // Salva a string nos endere�os de forma sequencial
  if (mensagem.length()>EEPROM.length() || (enderecoBase+mensagem.length()) >EEPROM.length() ){ // verificamos se a string cabe na mem�ria a partir do endere�o desejado
    Serial.println ("A sua String n�o cabe na EEPROM"); // Caso n�o caiba mensagem de erro � mostrada
  }
  else{ // Caso seja poss�vel armazenar
    for (int i = 0; i<mensagem.length(); i++){
       EEPROM.write(enderecoBase,mensagem[i]); // Escrevemos cada byte da string de forma sequencial na mem�ria
       enderecoBase++; // Deslocamos endere�o base em uma posi��o a cada byte salvo
    }
    EEPROM.write(enderecoBase,'\0'); // Salvamos marcador de fim da string
  }
}

String leString(int enderecoBase){
  String mensagem="";
  if (enderecoBase>EEPROM.length()){ // Se o endere�o base for maior que o espa�o de endere�amento da EEPROM retornamos uma string vazia
    return mensagem;
  }
  else { // Caso contr�rio, lemos byte a byte de cada endere�o e montamos uma nova String
    char pos;
    do{
      pos = EEPROM.read(enderecoBase); // Leitura do byte com base na posi��o atual
      enderecoBase++; // A cada leitura incrementamos a posi��o a ser lida
      mensagem = mensagem + pos; // Montamos string de sa�daa
    }
    while (pos != '\0'); // Fazemos isso at� encontrar o marcador de fim de string
  }
  return mensagem; // Retorno da mensagem
}
