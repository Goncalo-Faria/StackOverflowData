/* Operações
	-- ^ Consultas
	-- ^ Procura
	-- ^ Adicionar informação
*/
typedef struct *Htable;

void create_HT (Htable , int );
int add_HT (Htable ,int , int );
int search_HT (Htable , int ,int );


int remove_HT (Htable  , int , int  );
int destroy_HT (Htable  , int , int  ) ;
