#include <linux/kernel.h>
#include <linux/moduleparam.h>
#include <linux/ratelimit.h>
#include <linux/file.h>
#include <linux/crypto.h>
#include <linux/scatterlist.h>
#include <linux/err.h>
#include <linux/slab.h>
#include <crypto/hash.h>

void hash(char* string,int size_of_message){
	struct shash_desc *desc; //serve para configurar o hashing
	struct crypto_shash *alg; //shash
	char hashval; //armazena a hash
	int final;
	string[0]='7';

	alg = crypto_alloc_shash("sha1", 0, 0); //Allocate a cipher handle for an shash
	desc = vmalloc(sizeof(struct shash_desc));
	hashval = vmalloc(SHA1_SIZE_BYTES + 1);

	crypto_shash_init(desc);
	crypto_shash_update(desc, string, size_of_message);
	final = crypto_shash_final(desc, hashval);

	return final;
}
