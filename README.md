name         : cbc(aes) <br>
driver       : cbc-aes-aesni <br>
module       : aesni_intel <br>
priority     : 400 <br>
refcnt       : 1 <br>
selftest     : passed <br>
internal     : no <br>
type         : skcipher <br>
async        : yes <br>
blocksize    : 16 <br>
min keysize  : 16 <br>
max keysize  : 32 <br>
ivsize       : 16 <br>
chunksize    : 16 <br>
walksize     : 16 <br>


alias showJournal='journalctl --since "1 hour ago" | grep kernel'^C
