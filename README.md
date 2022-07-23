# Basic NFT Code

## How to build and deploy

Run the commands
```  
cd build
cmake ..
make  
```
After build, the built smart contract is under the 'nft' directory in the 'build' directory, run the commands to deploy
```
cleos set contract your_eos_account ./nft
```

## How to issue NFTs

```
import { createCol, createAsset } from './scripts/actions.js';

(async () => {
  const collection = {
    author: 'your-eos-account',
    royalty: 0, // 10000 means 100%
    name: 'NFT Collection Name',
    description: 'NFT Collection Description',
    image: 'https://ipfs.io/ipfs/xxxxxxxx',
    banner: 'https://ipfs.io/ipfs/yyyyyyyy',
    links: {
      url: 'https://your-website.io/',
      twitter: 'https://twitter.com/your-twitter',
    },
  };
  let result = await createCol(collection);
  console.log(result);

  await  new Promise(resolve => setTimeout(resolve, 2000));

  for (let i = 1; i <= 10; i++) {
    const asset = {
      collection_id: 1,
      supply: 1,
      max_supply: 1,
      name: 'NFT Name #' + i,
      description: 'NFT description',
      image: 'https://ipfs.io/ipfs/zzzzzzzz',
      // animation_url: '',
      // external_url: '',
      attributes: [
        { trait_type: 'number', value: '#' + i },
      ],
    };
    result = await createAsset(asset);
    console.log(result);
  }
})();
```
For more usage, see scripts/example.js

 