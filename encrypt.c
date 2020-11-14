/*
   Gabriel Gonçalves Mattos Santini -  18189084
	Luiz Vinicius dos Santos Ruoso - 18233486
   Marcelo Germani Olmos -  18048298    
   Victor Felipe dos Santos -  18117820
   Victor Luiz Fraga Soldera - 18045674
*/

#include <linux/init.h>           // Macros used to mark up functions e.g. __init __exit
#include <linux/module.h>         // Core header for loading LKMs into the kernel
#include <linux/device.h>         // Header to support the kernel Driver Model
#include <linux/kernel.h>         // Contains types, macros, functions for the kernel
#include <linux/fs.h>             // Header for the Linux file system support
#include <linux/uaccess.h>        // Required for the copy to user function
#include <linux/mutex.h>	  // Required for the mutex functionality
#include <linux/moduleparam.h>

#include <crypto/hash.h>
#include <linux/stat.h>
#include <linux/crypto.h>
#include <linux/random.h>
#include <linux/mm.h>
#include <linux/scatterlist.h>
#include <crypto/skcipher.h>
#include <linux/err.h>
#include <linux/vmalloc.h>

struct skcipher_def {
    struct scatterlist sg; 
    struct crypto_skcipher *tfm;
    struct skcipher_request *req; //struct com definições para solicitar a criptografia
    struct crypto_wait wait; // struct para requisicao
};


void encrypt(char *string,int size_of_string ,char* localKey, char* iv);
static unsigned int test_skcipher_encdec(struct skcipher_def *sk, int enc);
static int test_skcipher( char msgToEncypt[], char keyFromUser[], char ivFromUser[]);




static unsigned int test_skcipher_encdec(struct skcipher_def *sk, int enc)
{
    int rc;
	char *resultdata = NULL;

    if (enc)
        rc = crypto_wait_req(crypto_skcipher_encrypt(sk->req), &sk->wait);
    else
        rc = crypto_wait_req(crypto_skcipher_decrypt(sk->req), &sk->wait);

    if (rc)
        printk("skcipher encrypt returned with result %d\n", rc);



    return rc;
}



static int test_skcipher( char msgToEncypt[], char keyFromUser[], char ivFromUser[]) //Inicia a encriptção da string
{
    struct skcipher_def sk;
    struct crypto_skcipher *skcipher = NULL;
    struct skcipher_request *req = NULL;
    char *scratchpad = NULL;
    char *ivdata = NULL;
    unsigned char key[32];
    int ret = -EFAULT;
	char *resultdata = NULL;
	int i=0;

    //printk("MSG: %s, Key: %s, IV: %s \n",msgToEncypt, keyFromUser, ivFromUser);


    skcipher = crypto_alloc_skcipher("cbc(aes)", 0, 0);
    if (IS_ERR(skcipher)) {
        pr_info("could not allocate skcipher handle\n");
        return PTR_ERR(skcipher);
    }

    req = skcipher_request_alloc(skcipher, GFP_KERNEL);
    if (!req) {
        pr_info("could not allocate skcipher request\n");
        ret = -ENOMEM;
        goto out;
    }

    skcipher_request_set_callback(req, CRYPTO_TFM_REQ_MAY_BACKLOG,
    	crypto_req_done,
        &sk.wait);


	strcpy(key, keyFromUser);
    if (crypto_skcipher_setkey(skcipher, key, 16)) {
        pr_info("key could not be set\n");
        ret = -EAGAIN;
        goto out;
    }
    print_hex_dump(KERN_DEBUG, "KEY: ", DUMP_PREFIX_NONE, 16, 1,
               key, 16, true);
			
		

    ivdata = vmalloc(16);
    if (!ivdata) {
        pr_info("could not allocate ivdata\n");
        goto out;
    }

	strcpy(ivdata, ivFromUser);

    scratchpad = vmalloc(16);
    if (!scratchpad) {
        pr_info("could not allocate scratchpad\n");
        goto out;
    }

	strcpy(scratchpad, msgToEncypt); // copiando string para cifrar


    sk.tfm = skcipher;
    sk.req = req;


    /* We encrypt one block */
    sg_init_one(&sk.sg, scratchpad, 16); //inicializa sk.sg com o conteudo do scratchpad
    skcipher_request_set_crypt(req, &sk.sg, &sk.sg, 16, ivdata);  // solicita a 
    crypto_init_wait(&sk.wait);

    /* encrypt data */
    ret = test_skcipher_encdec(&sk, 1);
    if (ret)
        goto out;


	resultdata = sg_virt(&sk.sg);
   
    strcpy(msgToEncypt, resultdata);
    pr_info("Encryption triggered successfully\n");

out:
    if (skcipher)
        crypto_free_skcipher(skcipher);
    if (req)
        skcipher_request_free(req);
    if (ivdata)
        vfree(ivdata);
    if (scratchpad)
        vfree(scratchpad);
    return ret;
}


void encrypt(char *string,int size_of_string ,char* localKey, char* iv){
    print_hex_dump(KERN_DEBUG, "String before: ", DUMP_PREFIX_NONE, 16, 1,
               string, 16, true);

    test_skcipher(string, localKey, iv);

    print_hex_dump(KERN_DEBUG, "String after: ", DUMP_PREFIX_NONE, 16, 1,
               string, 16, true);
	return;
}