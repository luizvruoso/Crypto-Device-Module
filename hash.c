#include <linux/kernel.h>
#include <linux/moduleparam.h>
#include <linux/ratelimit.h>
#include <linux/file.h>
#include <linux/crypto.h>
#include <linux/scatterlist.h>
#include <linux/err.h>
#include <linux/slab.h>
#include <crypto/hash.h>

#define SIZE_SHA1 20 //Em bytes

void hash(char* string,int size_of_message){
	struct shash_desc *desc; //Serve para configurar o hashing type
	struct crypto_shash *tfm; //Variavel que vai receber cipher handle
	char *hashval; //Armazena a hash da nossa sting
	int final;
	string[0]='7';

	tfm = crypto_alloc_shash("sha1", 0, 0); //Allocate a cipher handle for an shash *(const char * alg_name, u32 type, u32 mask)* 
	desc = vmalloc(sizeof(struct shash_desc));
    if(!desc)goto hash_skip;

    desc->tfm = tfm; //Iniciando variavel
    desc->flags = 0x0; //Iniciando variavel

	hashval = vmalloc(SIZE_SHA1 + 1);
    if(!hashval)goto hash_skip;

	crypto_shash_init(desc); //Configures hashing engine according to the supplied hash_desc
	crypto_shash_update(desc, string, size_of_message); //Performs the actual hashing method on sting
	final = crypto_shash_final(desc, hashval); //Sends hash to character array

hash_skip:
    if(tfm) crypto_free_shash(tfm);
    if(desc) vfree(desc);
    if(hashval) vfree(hashval);
    return final;
}

